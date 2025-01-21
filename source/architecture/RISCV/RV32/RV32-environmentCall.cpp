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

#include "RV32-environmentCall.hpp"

namespace distortos
{

namespace architecture
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

__attribute__ ((naked))
int supervisorCall(int (& function)(int, int, int, int), const int argument1, const int argument2, const int argument3,
		const int argument4)
{
	asm volatile
	(
			"							\n"
			"	j		.				\n"	// return
	);

	__builtin_unreachable();

	// suppress warnings
	(void)function;
	(void)argument1;
	(void)argument2;
	(void)argument3;
	(void)argument4;
}

}	// namespace architecture

}	// namespace distortos
