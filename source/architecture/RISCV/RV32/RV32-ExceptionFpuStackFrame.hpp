/**
 * \file
 * \brief ExceptionFpuStackFrame struct header
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONFPUSTACKFRAME_HPP_
#define SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONFPUSTACKFRAME_HPP_

namespace distortos
{

namespace architecture
{

/// stack frame for ARMv7-M and ARMv8-M created by hardware on exception entry when FPU context is active
struct ExceptionFpuStackFrame
{
	/// stack frame created by hardware on exception entry

#if __riscv_float_abi_single == 1
#endif	// __riscv_float_abi_single == 1
};

}	// namespace architecture

}	// namespace distortos

#endif	// SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONFPUSTACKFRAME_HPP_
