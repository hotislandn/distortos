/**
 * \file
 * \brief Low-level architecture initializer for RV32
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/BIND_LOW_LEVEL_INITIALIZER.h"

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
 * \brief Low-level architecture initializer for RV32
 *
 * This function is called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void architectureLowLevelInitializer()
{
#if __riscv_float_abi_single == 1
#endif	// __riscv_float_abi_single == 1
}

BIND_LOW_LEVEL_INITIALIZER(30, architectureLowLevelInitializer);

}	// namespace

}	// namespace architecture

}	// namespace distortos
