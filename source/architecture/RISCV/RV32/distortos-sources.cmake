#
# file: distortos-sources.cmake
#
# author: Copyright (C) 2018-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

target_include_directories(distortos PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/external/riscv)

target_sources(distortos PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/RV32-architectureLowLevelInitializer.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-disableInterruptMasking.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-enableInterruptMasking.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-exceptionCommon.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-getMainStack.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-initializeStack.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-isInInterruptContext.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-MSWI_Handler.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-requestContextSwitch.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-requestFunctionExecution.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-Reset_Handler.S
	${CMAKE_CURRENT_LIST_DIR}/RV32-restoreInterruptMasking.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-startScheduling.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-environmentCall.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-ECALL_Handler.cpp
	${CMAKE_CURRENT_LIST_DIR}/RV32-MTimer_Handler.cpp)

doxygen(INPUT ${CMAKE_CURRENT_LIST_DIR}
		INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/external/riscv
		EXCLUDE ${CMAKE_CURRENT_LIST_DIR}/external)
