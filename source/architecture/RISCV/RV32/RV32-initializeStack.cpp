/**
 * \file
 * \brief initializeStack() implementation for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/architecture/initializeStack.hpp"

#include "RV32-StackFrame.hpp"

#include "distortos/internal/scheduler/threadRunner.hpp"

#include <cerrno>

namespace distortos
{

namespace architecture
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

std::pair<int, void*> initializeStack(void* const buffer, const size_t size, internal::RunnableThread& runnableThread)
{
	const auto stackFrame = reinterpret_cast<StackFrame*>(static_cast<uint8_t*>(buffer) + size) - 1;
	if (stackFrame < buffer)
		return {ENOSPC, {}};

	stackFrame->softwareStackFrame.s0 = reinterpret_cast<void*>(0x08080808);
	stackFrame->softwareStackFrame.s1 = reinterpret_cast<void*>(0x09090909);
	stackFrame->softwareStackFrame.s2 = reinterpret_cast<void*>(0x18181818);
	stackFrame->softwareStackFrame.s3 = reinterpret_cast<void*>(0x19191919);
	stackFrame->softwareStackFrame.s4 = reinterpret_cast<void*>(0x20202020);
	stackFrame->softwareStackFrame.s5 = reinterpret_cast<void*>(0x21212121);
	stackFrame->softwareStackFrame.s6 = reinterpret_cast<void*>(0x22222222);
	stackFrame->softwareStackFrame.s7 = reinterpret_cast<void*>(0x23232323);
	stackFrame->softwareStackFrame.s8 = reinterpret_cast<void*>(0x24242424);
	stackFrame->softwareStackFrame.s9 = reinterpret_cast<void*>(0x25252525);
	stackFrame->softwareStackFrame.s10 = reinterpret_cast<void*>(0x26262626);
	stackFrame->softwareStackFrame.s11 = reinterpret_cast<void*>(0x27272727);
#if __riscv_float_abi_single == 1
#endif	// __riscv_float_abi_single == 1

	stackFrame->exceptionStackFrame.a0 = &runnableThread;
	stackFrame->exceptionStackFrame.a1 = reinterpret_cast<void*>(0x11111111);
	stackFrame->exceptionStackFrame.a2 = reinterpret_cast<void*>(0x12121212);
	stackFrame->exceptionStackFrame.a3 = reinterpret_cast<void*>(0x13131313);
	stackFrame->exceptionStackFrame.a4 = reinterpret_cast<void*>(0x14141414);
	stackFrame->exceptionStackFrame.a5 = reinterpret_cast<void*>(0x15151515);
	stackFrame->exceptionStackFrame.a6 = reinterpret_cast<void*>(0x16161616);
	stackFrame->exceptionStackFrame.a7 = reinterpret_cast<void*>(0x17171717);
	stackFrame->exceptionStackFrame.t0 = reinterpret_cast<void*>(0x05050505);
	stackFrame->exceptionStackFrame.t1 = reinterpret_cast<void*>(0x06060606);
	stackFrame->exceptionStackFrame.t2 = reinterpret_cast<void*>(0x07070707);
	stackFrame->exceptionStackFrame.t3 = reinterpret_cast<void*>(0x28282828);
	stackFrame->exceptionStackFrame.t4 = reinterpret_cast<void*>(0x29292929);
	stackFrame->exceptionStackFrame.t5 = reinterpret_cast<void*>(0x30303030);
	stackFrame->exceptionStackFrame.t6 = reinterpret_cast<void*>(0x31313131);
	stackFrame->exceptionStackFrame.ra = nullptr;
	stackFrame->exceptionStackFrame.pc = reinterpret_cast<void*>(&internal::threadRunner);
	stackFrame->exceptionStackFrame.status = reinterpret_cast<void*>(ExceptionStackFrame::defaultStatus);

	return {{}, stackFrame};
}

}	// namespace architecture

}	// namespace distortos
