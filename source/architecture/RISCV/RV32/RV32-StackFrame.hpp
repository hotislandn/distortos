/**
 * \file
 * \brief StackFrame struct header
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_ARCHITECTURE_RISCV_RV32_STACKFRAME_HPP_
#define SOURCE_ARCHITECTURE_RISCV_RV32_STACKFRAME_HPP_

#include "RV32-ExceptionStackFrame.hpp"
#include "RV32-SoftwareStackFrame.hpp"

namespace distortos
{

namespace architecture
{

/// complete stack frame of thread for RV32
struct StackFrame
{
#if __riscv_float_abi_single == 1
#endif	// __riscv_float_abi_single == 1
	/// stack frame created by software during context switch
	SoftwareStackFrame softwareStackFrame;
	/// stack frame created by hardware on exception entry
	ExceptionStackFrame exceptionStackFrame;
};

}	// namespace architecture

}	// namespace distortos

#endif	// SOURCE_ARCHITECTURE_RISCV_RV32_STACKFRAME_HPP_
