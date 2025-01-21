/**
 * \file
 * \brief disableInterruptMasking() implementation for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/architecture/disableInterruptMasking.hpp"

namespace distortos
{

namespace architecture
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

InterruptMask disableInterruptMasking()
{
	InterruptMask interruptMask;

	asm volatile
	(
		"csrrsi %[interruptMask], mstatus, 8"
		: [interruptMask] "=r" (interruptMask)
		:
		:
	);

	return interruptMask;
}

}	// namespace architecture

}	// namespace distortos
