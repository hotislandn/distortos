/**
 * \file
 * \brief ECALL_Handler() for RV32
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief ECALL_Handler() for RV32
 *
 * Calls provided function with arguments.
 */

extern "C" __attribute__ ((naked)) void ECALL_Handler()
{
	asm volatile
	(
			"	ebreak						\n"
			"	j		.					\n"
	);

	__builtin_unreachable();
}
