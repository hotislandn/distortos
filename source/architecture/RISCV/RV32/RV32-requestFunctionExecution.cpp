/**
 * \file
 * \brief requestFunctionExecution() implementation for RV32
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/architecture/requestFunctionExecution.hpp"

#include "distortos/architecture/isInInterruptContext.hpp"

#if __riscv_float_abi_single == 1
#endif	// __riscv_float_abi_single == 1

#include "RV32-StackFrame.hpp"
#include "RV32-environmentCall.hpp"

#include "distortos/internal/scheduler/Scheduler.hpp"
#include "distortos/internal/scheduler/getScheduler.hpp"

#include "distortos/FATAL_ERROR.h"

#include <cerrno>
#include <cstring>

namespace distortos
{

namespace architecture
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Removes stack frame inserted by requestFunctionExecution() in case of interrupt -> current thread request.
 *
 * \param [in] savedStackPointer is the stack pointer value before new stack frame was created
 * \param [in] fpuContextActive (only when FPU is enabled) tells whether thread has active FPU context (true) or not
 * (false)
 */

__attribute__ ((naked))
#if __riscv_float_abi_single == 1
void removeStackFrame(const void* const savedStackPointer, const bool fpuContextActive)
#else	// __riscv_float_abi_single != 1
void removeStackFrame(const void* const savedStackPointer)
#endif	//  __riscv_float_abi_single = 1
{
	asm volatile
	(
			"	j		.							\n"	// return
	);
}

/**
 * \brief Trampoline used to execute function on new stack frame.
 *
 * After the function returns stack frame is removed and old stack pointer value is restored.
 *
 * \param [in] function is a reference to function that will be executed
 * \param [in] savedStackPointer is the stack pointer value before new stack frame was created
 * \param [in] fullContext is an information about type of previous stack frame - "full", when the thread was not
 * running (true) or "interrupt", when the thread was running and was interrupted (false)
 */

__attribute__ ((naked))
void functionTrampoline(void (& function)(), const void* const savedStackPointer, const bool fullContext)
{
	using SupervisorCall = int(int (&)(int, int, int, int), int, int, int, int);	// type of supervisorCall()

	asm volatile
	(
			"	ebreak									\n"
			"	j			.							\n"	// jump to supervisorCall(), this does not return
	);

	__builtin_unreachable();
}

/**
 * \brief Handles request coming from interrupt context to execute provided function in current thread.
 *
 * \param [in] threadControlBlock is a reference to ThreadControlBlock of current thread
 * \param [in] function is a reference to function that should be executed in current thread
 *
 * \return 0 on success, error code otherwise:
 * - ENOSPC - amount of free stack is too small to request function execution;
 */

int fromInterruptToCurrentThread(internal::ThreadControlBlock& threadControlBlock, void (& function)())
{
	const auto stackPointer = 0; //__get_PSP();
	while(1);
#if __riscv_float_abi_single == 1

	// it's not possible to know whether the thread has active FPU context, so the only option is to assume it does
	const auto exceptionFpuStackFrame = reinterpret_cast<ExceptionFpuStackFrame*>(stackPointer) - 1;
	const auto exceptionStackFrame = &exceptionFpuStackFrame->exceptionStackFrame;

#else	// __riscv_float_abi_single != 1

	const auto exceptionStackFrame = reinterpret_cast<ExceptionStackFrame*>(stackPointer) - 1;

#endif	// __riscv_float_abi_single != 1

	if (threadControlBlock.getStack().checkStackPointer(exceptionStackFrame) == false)
		return ENOSPC;

#if __riscv_float_abi_single == 1

	const auto fpccr = FPU->FPCCR;
	// last FPU stack frame was allocated in thread mode and the stacking is still pending?
	// this condition will be false in following situations:
	// - thread doesn't use FPU - there was no FPU stack frame allocated in thread mode,
	// - thread uses FPU, but the registers are already stacked.
	if ((fpccr & FPU_FPCCR_THREAD_Msk) != 0 && (fpccr & FPU_FPCCR_LSPACT_Msk) != 0)
		asm volatile ("vmov s0, s0" ::: "memory");	// force stacking of FPU context

	memset(exceptionFpuStackFrame, 0, sizeof(*exceptionFpuStackFrame));
	exceptionFpuStackFrame->fpscr = reinterpret_cast<void*>(FPU->FPDSCR);

#endif	// __riscv_float_abi_single = 1

	exceptionStackFrame->a0 = reinterpret_cast<void*>(&function);
	exceptionStackFrame->a1 = reinterpret_cast<void*>(stackPointer);
	exceptionStackFrame->a2 = reinterpret_cast<void*>(false);
	exceptionStackFrame->a3 = reinterpret_cast<void*>(0x13131313);
	exceptionStackFrame->a4 = reinterpret_cast<void*>(0x14141414);
	exceptionStackFrame->ra = nullptr;
	exceptionStackFrame->pc = reinterpret_cast<void*>(&functionTrampoline);
	exceptionStackFrame->status = reinterpret_cast<void*>(ExceptionStackFrame::defaultStatus);

	//__set_PSP(reinterpret_cast<uint32_t>(exceptionStackFrame));
	return 0;
}

/**
 * \brief Handles request to execute provided function in non-current thread.
 *
 * \param [in] threadControlBlock is a reference to internal::ThreadControlBlock of thread in which \a function should
 * be executed
 * \param [in] function is a reference to function that should be executed in thread associated with
 * \a threadControlBlock
 *
 * \return 0 on success, error code otherwise:
 * - ENOSPC - amount of free stack is too small to request function execution;
 */

int toNonCurrentThread(internal::ThreadControlBlock& threadControlBlock, void (& function)())
{
	auto& stack = threadControlBlock.getStack();
	const auto stackPointer = stack.getStackPointer();
	const auto stackFrame = reinterpret_cast<StackFrame*>(stackPointer) - 1;
	if (stack.checkStackPointer(stackFrame) == false)
		return ENOSPC;

	stackFrame->softwareStackFrame.s0 = reinterpret_cast<void*>(0x44444444);
	stackFrame->softwareStackFrame.s1 = reinterpret_cast<void*>(0x55555555);
	stackFrame->softwareStackFrame.s2 = reinterpret_cast<void*>(0x66666666);
	stackFrame->softwareStackFrame.s3 = reinterpret_cast<void*>(0x77777777);
	stackFrame->softwareStackFrame.s4 = reinterpret_cast<void*>(0x88888888);
	stackFrame->softwareStackFrame.s5 = reinterpret_cast<void*>(0x99999999);
	stackFrame->softwareStackFrame.s6 = reinterpret_cast<void*>(0xaaaaaaaa);
	stackFrame->softwareStackFrame.s7 = reinterpret_cast<void*>(0xbbbbbbbb);
	stackFrame->softwareStackFrame.s8 = reinterpret_cast<void*>(0xbbbbbbbb);
	stackFrame->softwareStackFrame.s9 = reinterpret_cast<void*>(0xbbbbbbbb);
	stackFrame->softwareStackFrame.s10 = reinterpret_cast<void*>(0xbbbbbbbb);
	stackFrame->softwareStackFrame.s11 = reinterpret_cast<void*>(0xbbbbbbbb);
#if __riscv_float_abi_single == 1
	stackFrame->softwareStackFrame.exceptionReturn =
			reinterpret_cast<void*>(SoftwareStackFrame::defaultExceptionReturn);
#endif	// __riscv_float_abi_single == 1

	stackFrame->exceptionStackFrame.a0 = reinterpret_cast<void*>(&function);
	stackFrame->exceptionStackFrame.a1 = reinterpret_cast<void*>(stackPointer);
	stackFrame->exceptionStackFrame.a2 = reinterpret_cast<void*>(true);
	stackFrame->exceptionStackFrame.a3 = reinterpret_cast<void*>(0x13131313);
	stackFrame->exceptionStackFrame.a4 = reinterpret_cast<void*>(0x14141414);
	stackFrame->exceptionStackFrame.ra = nullptr;
	stackFrame->exceptionStackFrame.pc = reinterpret_cast<void*>(&functionTrampoline);
	stackFrame->exceptionStackFrame.status = reinterpret_cast<void*>(ExceptionStackFrame::defaultStatus);

	stack.setStackPointer(stackFrame);
	return 0;
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

int requestFunctionExecution(internal::ThreadControlBlock& threadControlBlock, void (& function)())
{
	const auto& currentThreadControlBlock = internal::getScheduler().getCurrentThreadControlBlock();
	if (&threadControlBlock != &currentThreadControlBlock)	// request to non-current thread?
		return toNonCurrentThread(threadControlBlock, function);

	if (isInInterruptContext() == true)	// interrupt is sending the request to current thread?
		return fromInterruptToCurrentThread(threadControlBlock, function);

	FATAL_ERROR("Current thread of execution is sending the request to itself!");
}

}	// namespace architecture

}	// namespace distortos
