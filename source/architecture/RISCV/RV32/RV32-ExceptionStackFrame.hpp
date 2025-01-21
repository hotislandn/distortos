/**
 * \file
 * \brief ExceptionStackFrame struct header
 *
 * \author Copyright (C) 2015-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONSTACKFRAME_HPP_
#define SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONSTACKFRAME_HPP_

#include <cstdint>

namespace distortos
{

namespace architecture
{

/// stack frame for RV32 created by SW on exception entry, with ABI naming
struct ExceptionStackFrame
{
	/// default value of xstatus register
	constexpr static uintptr_t defaultStatus {0x00001880};

	void* status;
	void* pc;
	void* ra;
	void* sp;
	void* tp;
	/// t register
	void* t0;
	void* t1;
	void* t2;
	void* t3;
	void* t4;
	void* t5;
	void* t6;
	/// a register
	void* a0;
	void* a1;
	void* a2;
	void* a3;
	void* a4;
	void* a5;
	void* a6;
	void* a7;
};

}	// namespace architecture

}	// namespace distortos

#endif	// SOURCE_ARCHITECTURE_RISCV_RV32_EXCEPTIONSTACKFRAME_HPP_
