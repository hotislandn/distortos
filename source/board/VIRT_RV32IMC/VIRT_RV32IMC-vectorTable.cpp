/**
 * \file
 * \brief VIRT,RV32IMC vector table
 *
 * \author Copyright (C) 2014-2019 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * \warning
 * Automatically generated file - do not edit!
 */

#include "distortos/chip/proxy.h"

#include "distortos/BIND_LOW_LEVEL_INITIALIZER.h"

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local types
+---------------------------------------------------------------------------------------------------------------------*/

/// single exception vector - pointer to function with no arguments and no return value
using ExceptionVector = void(*)();

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// priority of interrupts
#if defined(DISTORTOS_ARCHITECTURE_KERNEL_BASEPRI)
constexpr uint8_t interruptPriority {DISTORTOS_ARCHITECTURE_KERNEL_BASEPRI};
#else	// !defined(DISTORTOS_ARCHITECTURE_KERNEL_BASEPRI)
constexpr uint8_t interruptPriority {};
#endif	// !defined(DISTORTOS_ARCHITECTURE_KERNEL_BASEPRI)

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Low-level peripheral initializer for NVIC
 *
 * This function is called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void clintLowLevelInitializer()
{
}

BIND_LOW_LEVEL_INITIALIZER(50, clintLowLevelInitializer);

}	// namespace

extern "C"
{

/*---------------------------------------------------------------------------------------------------------------------+
| default handlers
+---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------+
| global symbols' declarations
+---------------------------------------------------------------------------------------------------------------------*/

extern const char __main_stack_end[];		// main stack end - imported from linker script

void Reset_Handler();		// import the address of Reset_Handler()

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

/// vector table
const ExceptionVector vectorTable[] __attribute__ ((section(".vectorTable"), used))
{
	0
};

}	// extern "C"
