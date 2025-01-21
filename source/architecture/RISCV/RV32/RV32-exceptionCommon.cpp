/**
 * \file
 * \brief supervisorCall() implementation for RV32
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <cstdint>

#include "distortos/internal/scheduler/getScheduler.hpp"
#include "distortos/internal/scheduler/Scheduler.hpp"

#include "RV32-exceptionCommon.hpp"

extern "C" __attribute__ ((naked)) void MSWI_Handler();
extern "C" void MTimer_Handler(const void* const sp);

namespace distortos
{

namespace architecture
{

bool isInThread = true;

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

extern "C" void* exceptionCommon(uintptr_t cause, uintptr_t epc, uintptr_t tval, StackFrame& frm)
{
	void *sp = reinterpret_cast<void* >(&frm);

	(void)epc;
	(void)tval;

	isInThread = false;

	if (cause & 0x80000000) {
		// interrupt
		switch(cause & 0xff) {
			case 3:
				MSWI_Handler();
#ifdef DISTORTOS_CHECK_STACK_POINTER_RANGE_CONTEXT_SWITCH_ENABLE
				if (internal::getScheduler().getCurrentThreadControlBlock().getStack().checkStackPointer(sp) == false)
					while(1);
#endif
				sp = internal::getScheduler().switchContext(reinterpret_cast<void* const>(&frm));
				break;

			case 7:
				MTimer_Handler(sp);
				break;

			case 11:
			default:
				while(1);
				break;
		}
	} else {
		// exception
		while(1);
	}

	isInThread = true;
	return sp;
}

}	// namespace architecture

}	// namespace distortos
