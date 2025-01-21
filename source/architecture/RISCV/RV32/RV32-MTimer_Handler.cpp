/**
 * \file
 * \brief SysTick_Handler() for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/internal/scheduler/getScheduler.hpp"
#include "distortos/internal/scheduler/Scheduler.hpp"

#include "distortos/architecture/requestContextSwitch.hpp"

#ifdef DISTORTOS_CHECK_STACK_POINTER_RANGE_SYSTEM_TICK_ENABLE

#include "distortos/FATAL_ERROR.h"

#endif	// def DISTORTOS_CHECK_STACK_POINTER_RANGE_SYSTEM_TICK_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief SysTick_Handler() for RV32
 *
 * Tick interrupt of scheduler. This function also checks stack pointer range when this functionality is enabled - if
 * the check fails, FATAL_ERROR() is called.
 */

extern "C" void MTimer_Handler(const void* const sp)
{
	auto& scheduler = distortos::internal::getScheduler();

#ifdef DISTORTOS_CHECK_STACK_POINTER_RANGE_SYSTEM_TICK_ENABLE

	if (scheduler.getCurrentThreadControlBlock().getStack().checkStackPointer(sp) == false)
		while(1); //FATAL_ERROR("Stack overflow detected!");

#endif	// def DISTORTOS_CHECK_STACK_POINTER_RANGE_SYSTEM_TICK_ENABLE

	const auto incr = DISTORTOS_CHIP_CPU_FREQUENCY / DISTORTOS_TICK_FREQUENCY;

	*(volatile uint64_t *)0x02004000 = *(volatile uint64_t *)0x0200bff8 + incr;

	const auto contextSwitchRequired = scheduler.tickInterruptHandler();
	if (contextSwitchRequired == true)
		distortos::architecture::requestContextSwitch();
}
