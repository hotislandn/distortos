#
# file: cmake/80-VIRT.cmake
#
# author: Copyright (C) 2018-2021 Kamil Szczygiel https://distortec.com https://freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Automatically generated file - do not edit!
#

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_VIRT
		ON)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_RV32IMC
		ON)

distortosSetFixedConfiguration(STRING
		DISTORTOS_CHIP
		"VIRT,RV32IMC")

distortosSetFixedConfiguration(INTEGER
		DISTORTOS_CHIP_VDD_MV
		3000)

distortosSetFixedConfiguration(INTEGER
		DISTORTOS_CHIP_CPU_FREQUENCY
		10000000)

# overide the default setting
distortosSetConfiguration(BOOLEAN
		distortos_Checks_00_Context_of_functions_rv
		ON
		HELP "Check context of functions.

		Some functions may only be used from thread context, as using them from interrupt context results in undefined
		behaviour. There are several groups of functions to which this restriction applies (some functions fall into
		several categories at once):
		- all blocking functions, like callOnce(), FifoQueue::push(), Semaphore::wait(), ..., as an attempt to block
		current thread of execution (not to be confused with current thread) is not possible in interrupt context;
		- all mutex functions, as the concept of ownership by a thread - core feature of mutex - cannot be fulfilled in
		interrupt context;
		- all functions from ThisThread namespace (including ThisThread::Signals namespace), as in interrupt context
		they would access a random thread that happened to be executing at that particular moment;

		Using such functions from interrupt context is a common bug in applications which can be easily introduced and
		very hard to find, as the symptoms may appear only under certain circumstances.

		Selecting this option enables context checks in all functions with such requirements. If any of them is used
		from interrupt context, FATAL_ERROR() will be called."
		OUTPUT_NAME DISTORTOS_CHECK_FUNCTION_CONTEXT_ENABLE)

distortosSetConfiguration(BOOLEAN
		distortos_Checks_01_Stack_pointer_range_during_context_switch_rv
		ON
		HELP "Check stack pointer range during context switch.

		Simple range checking of preempted thread's stack pointer can be performed during context switches. It is
		relatively fast, but cannot detect all stack overflows. The check is done before the software stack frame is
		pushed on thread's stack, but the size of this pending stack frame is accounted for - the intent is to detect a
		stack overflow which is about to happen, before it can cause (further) data corrution. FATAL_ERROR() will be
		called if the stack pointer is outside valid range."
		OUTPUT_NAME DISTORTOS_CHECK_STACK_POINTER_RANGE_CONTEXT_SWITCH_ENABLE)

distortosSetConfiguration(BOOLEAN
		distortos_Checks_02_Stack_pointer_range_during_system_tick_rv
		ON
		HELP "Check stack pointer range during system tick.

		Similar to \"distortos_Checks_01_Stack_pointer_range_during_context_switch\", but executed during every system
		tick."
		OUTPUT_NAME DISTORTOS_CHECK_STACK_POINTER_RANGE_SYSTEM_TICK_ENABLE)

distortosSetConfiguration(BOOLEAN
		distortos_Scheduler_03_Support_for_thread_detachment_rv
		ON
		HELP "Enable support for thread detachment.

		Enable functions that \"detach\" dynamic threads:
		- ThisThread::detach();
		- Thread::detach();

		When this options is not selected, these functions are not available at all.

		When dynamic and detached thread terminates, it will be added to the global list of threads pending for deferred
		deletion. The thread will actually be deleted in idle thread, but only when two mutexes are successfully locked:
		- mutex that protects dynamic memory allocator;
		- mutex that synchronizes access to the list of threads pending for deferred deletion;"
		OUTPUT_NAME DISTORTOS_THREAD_DETACH_ENABLE)

include("${CMAKE_CURRENT_SOURCE_DIR}/source/chip/VIRT/RV32IMC/distortos-sources.cmake")
