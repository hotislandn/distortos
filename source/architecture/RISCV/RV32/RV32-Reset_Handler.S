/**
 * \file
 * \brief Reset_Handler() for RV32
 *
 * \author Copyright (C) 2014-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Reset_Handler() for RV32
 */

.global Reset_Handler
.section .text.Reset_Handler
Reset_Handler:
		csrci   mstatus, 8
		csrw    mie, zero
		csrw    mip, zero

	.option push
	.option norelax
		la      gp, __global_pointer$
	.option pop

		li      a0, 0x02004000
		li      a1, -1
		sw      a1, 4(a0)
		sw      a1, 0(a0)

		li      a0, 0x0200c000
		sw      zero, -8(a0)
		sw      zero, -4(a0)

		lla     a0, 100f
		csrw	mtvec, a0

		la      sp, __main_stack_end
		andi    sp, sp, -16
		csrw	mscratch, sp
		la      sp, __process_stack_end
		andi    sp, sp, -16

		la      s0, __low_level_preinitializers_start
		la      s1, __low_level_preinitializers_end

		beq     s0, s1, 2f
	1:
		lw      s2, (s0)
		addi    s0, s0, 4
		jalr    s2
		bne     s0, s1, 1b
	2:
		nop

		la      a0, __data_initializers_start
		la      a1, __data_initializers_end

	1:
		bgeu    a0, a1, 3f
		lw      a2, 0(a0)
		lw      a3, 4(a0)
		lw      a4, 8(a0)
		addi    a0, a0, 12
		beq     a3, a4, 1b

	2:
		lw      a5, (a2)
		addi    a2, a2, 4
		sw      a5, (a3)
		addi    a3, a3, 4
		bltu    a3, a4, 2b

		j       1b
	3:
		nop

		la      a0, __bss_initializers_start
		la      a1, __bss_initializers_end

	1:
		bgeu    a0, a1, 3f
		lw      a2, 0(a0)
		lw      a3, 4(a0)
		lw      a4, 8(a0)
		addi    a0, a0, 12
		beq     a3, a4, 1b

	2:
		sw      a2, (a3)
		addi    a3, a3, 4
		bltu    a3, a4, 2b

		j       1b
	3:
		nop

		la      s0, __low_level_initializers_start
		la      s1, __low_level_initializers_end

		bgeu    s0, s1, 2f
	1:
		lw      s2, (s0)
		addi    s0, s0, 4
		jalr    s2
		bltu    s0, s1, 1b
	2:
		nop

		call    __libc_init_array

		nop
		la      a0, main
		csrw    mepc, a0
		li      a0, 0x1880
		csrw    mstatus, a0
		li      a0, 0x88
		csrw    mie, a0
		mret

		j       .

	.align 8
	.extern exceptionCommon
	100:
		addi	sp, sp, -128

		sw      s0,   0(sp)
		sw      s1,   4(sp)
		sw      s2,   8(sp)
		sw      s3,  12(sp)
		sw      s4,  16(sp)
		sw      s5,  20(sp)
		sw      s6,  24(sp)
		sw      s7,  28(sp)
		sw      s8,  32(sp)
		sw      s9,  36(sp)
		sw      s10, 40(sp)
		sw      s11, 44(sp)

		/* 48 - mstatus */
		/* 52 - mepc */
		sw      ra,  56(sp)
		/* 60 - sp */
		sw      tp,  64(sp)

		sw      t0,  68(sp)
		sw      t1,  72(sp)
		sw      t2,  76(sp)
		sw      t3,  80(sp)
		sw      t4,  84(sp)
		sw      t5,  88(sp)
		sw      t6,  92(sp)

		sw      a0,  96(sp)
		sw      a1, 100(sp)
		sw      a2, 104(sp)
		sw      a3, 108(sp)
		sw      a4, 112(sp)
		sw      a5, 116(sp)
		sw      a6, 120(sp)
		sw      a7, 124(sp)

		csrr    a0, mstatus
		sw      a0,  48(sp)
		csrr    a1, mepc
		sw      a1,  52(sp)
		csrr    a2, mtval
		mv      a3, sp
		csrr    a0, mcause

		call    exceptionCommon
		mv      sp, a0

		lw      a0,  52(sp)
		csrw    mepc, a0
		lw      a1,  48(sp)
		csrw    mstatus, a1

		lw      a7, 124(sp)
		lw      a6, 120(sp)
		lw      a5, 116(sp)
		lw      a4, 112(sp)
		lw      a3, 108(sp)
		lw      a2, 104(sp)
		lw      a1, 100(sp)
		lw      a0,  96(sp)

		lw      t6,  92(sp)
		lw      t5,  88(sp)
		lw      t4,  84(sp)
		lw      t3,  80(sp)
		lw      t2,  76(sp)
		lw      t1,  72(sp)
		lw      t0,  68(sp)

		lw      tp,  64(sp)
		lw      ra,  56(sp)

		lw      s11, 44(sp)
		lw      s10, 40(sp)
		lw      s9,  36(sp)
		lw      s8,  32(sp)
		lw      s7,  28(sp)
		lw      s6,  24(sp)
		lw      s5,  20(sp)
		lw      s4,  16(sp)
		lw      s3,  12(sp)
		lw      s2,   8(sp)
		lw      s1,   4(sp)
		lw      s0,   0(sp)

		addi    sp, sp, 128
		mret

.end