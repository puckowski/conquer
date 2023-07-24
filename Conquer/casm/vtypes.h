
#ifndef VTYPES_H
#define VTYPES_H

#include <cstdint>

namespace violet
{
	const uint32_t REGS_N{ 4 };

	enum instructions : uint32_t
	{
		// Integer instructions
		i_add = 0,
		i_cmp = 1,
		i_dec = 2,
		i_div = 3,
		i_hlt = 4,
		i_inc = 5,
		i_ja = 6,
		i_jb = 7,
		i_je = 8,
		i_jmp = 9,
		i_jne = 10,
		i_jnz = 11,
		i_jz = 12,
		i_mov = 13,
		i_movi = 14,
		i_mul = 15,
		i_not = 16,
		i_or = 17,
		i_pop = 18,
		i_push = 19,
		i_pushi = 20,
		i_sub = 21,
		i_xor = 22,

		// Data instructions
		i_lab = 23,

		//
		i_fadd = 24,
		i_fdiv = 25,
		i_fmovi = 26,
		i_fmul = 27,
		i_fpush = 28,
		i_fpushi = 29,
		i_fsub = 30,
	};

	struct instruction
	{
		uint32_t code;
		//uint32_t data;

		uint32_t r0;
		uint32_t r1;
		uint32_t r2;
		uint32_t r3;
	};
}

#endif // VTYPES_H