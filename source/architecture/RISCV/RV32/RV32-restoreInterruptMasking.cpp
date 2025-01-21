/**
 * \file
 * \brief restoreInterruptMasking() implementation for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/architecture/restoreInterruptMasking.hpp"

namespace distortos
{

namespace architecture
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void restoreInterruptMasking(const InterruptMask interruptMask)
{
	if (interruptMask & 8) {
		asm volatile ("csrrsi	zero, mstatus, 8":::);
	} else {
		asm volatile ("csrrci   zero, mstatus, 8":::);
	}
}

}	// namespace architecture

}	// namespace distortos
