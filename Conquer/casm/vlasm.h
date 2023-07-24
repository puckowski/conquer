
#ifndef VLASM_H
#define VLASM_H

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

#include "vtypes.h"

namespace violet
{
	namespace vlasm
	{
		const char comment(';');
		const std::string i_add("add");
		const std::string i_cmp("cmp");
		const std::string i_dec("dec");
		const std::string i_div("div");
		const std::string i_hlt("hlt");
		const std::string i_inc("inc");
		const std::string i_ja("ja");
		const std::string i_jb("jb");
		const std::string i_je("je");
		const std::string i_jmp("jmp");
		const std::string i_jne("jne");
		const std::string i_jnz("jnz");
		const std::string i_jz("jz");
		const std::string i_mov("mov");
		const std::string i_movi("movi");
		const std::string i_mul("mul");
		const std::string i_not("not");
		const std::string i_or("or");
		const std::string i_pop("pop");
		const std::string i_push("push");
		const std::string i_pushi("pushi");
		const std::string i_sub("sub");
		const std::string i_xor("xor");
		const std::string i_lab("lab");
		const std::string i_fadd("fadd");
		const std::string i_fdiv("fdiv");
		const std::string i_fmovi("fmovi");
		const std::string i_fmul("fmul");
		const std::string i_fpush("fpush");
		const std::string i_fpushi("fpushi");
		const std::string i_fsub("fsub");

		const std::unordered_map<std::string, uint32_t> 
			registers {
				{"r0", 0},
				{"r1", 1},
				{"r2", 2},
				{"r3", 3}
		};

		extern std::map<std::string, uint32_t> gLabelMap;
		extern std::map<std::string, uint32_t> gMessageMap;
		extern uint32_t pc;

		std::vector<uint32_t> parse_source(const std::vector<std::string>);
		std::vector<std::string> parse_line(const std::string);
		void parse_tokens_for_data(std::vector<uint32_t> &program, std::vector<std::string> tokens);
		void parse_tokens(std::vector<uint32_t> &program, std::vector<std::string> tokens);
		uint32_t parse_reg(const std::string);
		void die(const std::string);
	};
}

#endif // VLASM_H