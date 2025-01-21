/**
 * \file
 * \brief exceptionCommon() declaration
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONCOMMON_HPP_
#define SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONCOMMON_HPP_

#include "RV32-StackFrame.hpp"

namespace distortos
{

namespace architecture
{

/**
 * \brief Common exception handler.
 *
 * common exception handler
 *
 * \param [in] cause
 * \param [in] epc
 * \param [in] tval
 * \param [in] frm
 *
 * \return stack frame
 */

extern "C" void* exceptionCommon(uintptr_t cause, uintptr_t epc, uintptr_t tval, StackFrame& frm);

}	// namespace architecture

}	// namespace distortos

#endif	// SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONCOMMON_HPP_
