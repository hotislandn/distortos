/**
 * \file
 * \brief Start of scheduling for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <cstdint>

#include "distortos/BIND_LOW_LEVEL_INITIALIZER.h"

namespace distortos
{

namespace architecture
{

namespace rv32
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Start of scheduling for RV32
 *
 * Initializes all required hardware/software to perform context switching and starts the scheduling. This function is
 * called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void startScheduling()
{
	// TODO: set mtimer
	*(volatile uint64_t *)0x02004000 = *(volatile uint64_t *)0x0200bff8 + 10000;
}

BIND_LOW_LEVEL_INITIALIZER(70, startScheduling);

}	// namespace

}	// namespace architecture

}	// namespace distortos
