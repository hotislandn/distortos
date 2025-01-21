/**
 * \file
 * \brief PendSV_Handler() for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/internal/scheduler/getScheduler.hpp"
#include "distortos/internal/scheduler/Scheduler.hpp"

#ifdef DISTORTOS_CHECK_STACK_POINTER_RANGE_CONTEXT_SWITCH_ENABLE

#include "distortos/FATAL_ERROR.h"

#endif	// def DISTORTOS_CHECK_STACK_POINTER_RANGE_CONTEXT_SWITCH_ENABLE

namespace distortos
{

namespace architecture
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef DISTORTOS_CHECK_STACK_POINTER_RANGE_CONTEXT_SWITCH_ENABLE

/**
 * \brief Wrapper for check of stack pointer range
 *
 * If the check fails, FATAL_ERROR() is called.
 *
 * \param [in] stackPointer is the current thread's stack pointer value, including the frame which will be stacked
 */

void checkStackPointerWrapper(const void* const stackPointer)
{
	if (internal::getScheduler().getCurrentThreadControlBlock().getStack().checkStackPointer(stackPointer) == false)
		FATAL_ERROR("Stack overflow detected!");
}

#endif	// def DISTORTOS_CHECK_STACK_POINTER_RANGE_CONTEXT_SWITCH_ENABLE

/**
 * \brief Wrapper for void* distortos::internal::getScheduler().switchContext(void*)
 *
 * \param [in] stackPointer is the current value of current thread's stack pointer
 *
 * \return new thread's stack pointer
 */

void* schedulerSwitchContextWrapper(void* const stackPointer)
{
	return internal::getScheduler().switchContext(stackPointer);
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief PendSV_Handler() for RV32
 *
 * Performs the context switch.
 */

extern "C" __attribute__ ((naked)) void MSWI_Handler()
{
	asm volatile
	(
			"	li	a0, 0x02000000				\n"	// return to new thread
			"	sw	zero, (a0)					\n"
			"	ret								\n"
	);

	__builtin_unreachable();
}

}	// namespace distortos

