/**
 * \file
 * \brief SoftwareStackFrame struct header
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_ARCHITECTURE_RISCV_RV32_SOFTWARESTACKFRAME_HPP_
#define SOURCE_ARCHITECTURE_RISCV_RV32_SOFTWARESTACKFRAME_HPP_

namespace distortos
{

namespace architecture
{

/// stack frame for ARMv6-M, ARMv7-M and ARMv8-M created by software during context switch
struct SoftwareStackFrame
{
#if __riscv_float_abi_single == 1
#endif	// __riscv_float_abi_single == 1

	/// s register
	void* s0;
	void* s1;
	void* s2;
	void* s3;
	void* s4;
	void* s5;
	void* s6;
	void* s7;
	void* s8;
	void* s9;
	void* s10;
	void* s11;
};

}	// namespace architecture

}	// namespace distortos

#endif	// SOURCE_ARCHITECTURE_RISCV_RV32_SOFTWARESTACKFRAME_HPP_
