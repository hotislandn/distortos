#
# file: distortos-sources.cmake
#
# author: Copyright (C) 2018-2020 Kamil Szczygiel https://distortec.com https://freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

distortosSetConfiguration(BOOLEAN
		distortos_chip_RISCV_has_clint
		ON
		HELP "riscv chip has clint"
		OUTPUT_NAME DISTORTOS_CHIP_RISCV_HAS_CLINT)

target_include_directories(distortos PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/external)

target_sources(distortos PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/RV32IMC-chipLowLevelInitializer.cpp)

doxygen(INPUT ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include
		INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/external
		EXCLUDE ${CMAKE_CURRENT_LIST_DIR}/external)
