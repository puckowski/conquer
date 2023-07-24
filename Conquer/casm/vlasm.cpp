
#define _SECURE_SCL_DEPRECATE 0

#ifndef VLASM_CPP
#define VLASM_CPP

#include <sstream>
#include <iostream>
#include <iterator>

#include "vlasm.h"

namespace violet
{
	namespace vlasm
	{
		char CHAR_NULL = '\0';
		char CHAR_SPACE = ' ';

		const uint32_t DATA_NULL = reinterpret_cast<uint32_t&>(CHAR_NULL) << 24;
		const uint32_t DATA_SPACE = reinterpret_cast<uint32_t&>(CHAR_SPACE) << 24;

		std::map<std::string, uint32_t> gLabelMap;
		std::map<std::string, uint32_t> gMessageMap;
		uint32_t pc;

		std::vector<uint32_t> parse_source(const std::vector<std::string> source)
		{
			std::vector<uint32_t> program;

			pc = 0;

			for (const auto& line : source)
			{
				if (line.empty() == true)
					continue;
				else if (line[0] == comment)
					continue;

				std::vector<std::string> tokens = parse_line(line);
				parse_tokens_for_data(program, tokens);
			}

			pc = 0;

			for (const auto& line : source)
			{
				if (line.empty() == true)
					continue;
				else if (line[0] == comment) 
					continue;
				
				std::vector<std::string> tokens = parse_line(line);
				parse_tokens(program, tokens);
			}

			return program;
		}

		std::vector<std::string> parse_line(const std::string line)
		{
			std::istringstream iss(line);

			std::vector<std::string> 
				tokens {
					std::istream_iterator<std::string>{iss},
					std::istream_iterator<std::string>{}
			};

			return tokens;
		}

		void parse_tokens_for_data(std::vector<uint32_t> &program, std::vector<std::string> tokens)
		{
			int i, n;

			if (tokens[0] == vlasm::i_add)
				pc++;
			else if (tokens[0] == vlasm::i_fadd)
				pc++;
			else if (tokens[0] == vlasm::i_cmp)
				pc++;
			else if (tokens[0] == vlasm::i_dec)
				pc++;
			else if (tokens[0] == vlasm::i_div)
				pc++;
			else if (tokens[0] == vlasm::i_fdiv)
				pc++;
			else if (tokens[0] == vlasm::i_hlt)
				pc++;
			else if (tokens[0] == vlasm::i_inc)
				pc++;
			else if (tokens[0] == vlasm::i_ja)
				pc += 2;
			else if (tokens[0] == vlasm::i_jb)
				pc += 2;
			else if (tokens[0] == vlasm::i_je)
				pc += 2;
			else if (tokens[0] == vlasm::i_jmp)
				pc += 2;
			else if (tokens[0] == vlasm::i_jne)
				pc += 2;
			else if (tokens[0] == vlasm::i_jnz)
				pc += 2;
			else if (tokens[0] == vlasm::i_jz)
				pc += 2;
			else if (tokens[0] == vlasm::i_mov)
				pc++;
			else if (tokens[0] == vlasm::i_movi)
				pc += 2;
			else if (tokens[0] == vlasm::i_fmovi)
				pc += 2;
			else if (tokens[0] == vlasm::i_mul)
				pc++;
			else if (tokens[0] == vlasm::i_fmul)
				pc++;
			else if (tokens[0] == vlasm::i_not)
				pc++;
			else if (tokens[0] == vlasm::i_or)
				pc++;
			else if (tokens[0] == vlasm::i_pop)
				pc++;
			else if (tokens[0] == vlasm::i_push)
				pc++;
			else if (tokens[0] == vlasm::i_pushi)
				pc += 2;
			else if (tokens[0] == vlasm::i_fpush)
				pc++;
			else if (tokens[0] == vlasm::i_fpushi)
				pc += 2;
			else if (tokens[0] == vlasm::i_sub)
				pc++;
			else if (tokens[0] == vlasm::i_fsub)
				pc++;
			else if (tokens[0] == vlasm::i_xor)
				pc++;			
			else if (tokens[0] == vlasm::i_lab)
			{
				if (tokens.size() < 2)
					die("Invalid label operation");

				gLabelMap.insert({ tokens[1], pc });
			}
			else
			{
				die("Invalid instruction found");
			}
		}

		void parse_tokens(std::vector<uint32_t> &program, std::vector<std::string> tokens)
		{
			uint32_t opcode, temporaryData;
			int i, n, temporaryIntData;
			float temporaryFloatData;

			if (tokens[0] == vlasm::i_add)
			{
				if (tokens.size() != 3)
					die("Invalid addition operation");

				opcode = violet::i_add;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fadd)
			{
				if (tokens.size() != 3)
					die("Invalid float addition operation");

				opcode = violet::i_fadd;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_cmp)
			{
				if (tokens.size() != 4)
					die("Invalid compare operation");

				opcode = violet::i_cmp;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[3]);
				opcode = opcode << 8;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_dec)
			{
				if (tokens.size() != 2)
					die("Invalid decrement operation");

				opcode = violet::i_dec;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_div)
			{
				if (tokens.size() != 3)
					die("Invalid division operation");

				opcode = violet::i_div;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fdiv)
			{
				if (tokens.size() != 3)
					die("Invalid float division operation");

				opcode = violet::i_fdiv;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_hlt)
			{
				opcode = violet::i_hlt;
				opcode = opcode << 24;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_inc)
			{
				if (tokens.size() != 2)
					die("Invalid increment operation");

				opcode = violet::i_inc;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_ja)
			{
				if (tokens.size() != 4)
					die("Invalid jump if above operation");

				opcode = violet::i_ja;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[3]))
				{
					program.push_back(gLabelMap.find(tokens[3])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[3]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_jb)
			{
				if (tokens.size() != 4)
					die("Invalid jump if below operation");

				opcode = violet::i_jb;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[3]))
				{
					program.push_back(gLabelMap.find(tokens[3])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[3]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_je)
			{
				if (tokens.size() != 4)
					die("Invalid jump if equal operation");

				opcode = violet::i_je;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[3]))
				{
					program.push_back(gLabelMap.find(tokens[3])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[3]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_jmp)
			{
				if (tokens.size() != 2)
					die("Invalid jump operation");

				opcode = violet::i_jmp;
				opcode = opcode << 24;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[1]))
				{
					program.push_back(gLabelMap.find(tokens[1])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[1]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_jne)
			{
				if (tokens.size() != 4)
					die("Invalid jump if not equal operation");

				opcode = violet::i_jne;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[3]))
				{
					program.push_back(gLabelMap.find(tokens[3])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[3]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_jnz)
			{
				if (tokens.size() != 4)
					die("Invalid jump if not zero operation");

				opcode = violet::i_jnz;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[3]))
				{
					program.push_back(gLabelMap.find(tokens[3])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[3]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_jz)
			{
				if (tokens.size() != 4)
					die("Invalid jump if zero operation");

				opcode = violet::i_jz;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;

				if (gLabelMap.count(tokens[3]))
				{
					program.push_back(gLabelMap.find(tokens[3])->second);
					pc++;
				}
				else
				{
					temporaryIntData = std::stoi(tokens[3]);
					temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

					program.push_back(temporaryData);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_mov)
			{
				if (tokens.size() != 3)
					die("Invalid mov operation");

				opcode = violet::i_mov;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;

				if (gMessageMap.count(tokens[2]))
				{
					opcode = opcode | gMessageMap.find(tokens[2])->second;
					opcode = opcode << 12;

					program.push_back(opcode);
					pc++;
				}
				else
				{
					opcode = opcode | parse_reg(tokens[2]);
					opcode = opcode << 12;

					program.push_back(opcode);
					pc++;
				}
			}
			else if (tokens[0] == vlasm::i_movi)
			{
				if (tokens.size() != 3)
					die("Invalid movi operation");

				opcode = violet::i_movi;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;

				temporaryIntData = std::stoi(tokens[2]);
				temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

				program.push_back(temporaryData);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fmovi)
			{
				if (tokens.size() != 3)
					die("Invalid float movi operation");

				opcode = violet::i_fmovi;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;

				temporaryFloatData = std::stof(tokens[2]);
				temporaryData = reinterpret_cast<uint32_t&>(temporaryFloatData);

				program.push_back(temporaryData);
				pc++;
			}
			else if (tokens[0] == vlasm::i_mul)
			{
				if (tokens.size() != 3)
					die("Invalid multiplication operation");

				opcode = violet::i_mul;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fmul)
			{
				if (tokens.size() != 3)
					die("Invalid float multiplication operation");

				opcode = violet::i_fmul;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_not)
			{
				if (tokens.size() != 3)
					die("Invalid not operation");

				opcode = violet::i_not;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_or)
			{
				if (tokens.size() != 3)
					die("Invalid or operation");

				opcode = violet::i_or;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_pop)
			{
				if (tokens.size() != 2)
					die("Invalid pop operation");

				opcode = violet::i_pop;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_push)
			{
				if (tokens.size() != 2)
					die("Invalid push operation");

				opcode = violet::i_push;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_pushi)
			{
				if (tokens.size() != 2)
					die("Invalid pushi operation");

				opcode = violet::i_pushi;
				opcode = opcode << 4;

				program.push_back(opcode);
				pc++;

				temporaryIntData = std::stoi(tokens[2]);
				temporaryData = reinterpret_cast<uint32_t&>(temporaryIntData);

				program.push_back(temporaryData);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fpush)
			{
				if (tokens.size() != 2)
					die("Invalid float push operation");

				opcode = violet::i_fpush;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 16;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fpushi)
			{
				if (tokens.size() != 2)
					die("Invalid float pushi operation");

				opcode = violet::i_fpushi;
				opcode = opcode << 24;

				program.push_back(opcode);
				pc++;

				temporaryFloatData = std::stof(tokens[1]);
				temporaryData = reinterpret_cast<uint32_t&>(temporaryFloatData);

				program.push_back(temporaryData);
				pc++;
			}
			else if (tokens[0] == vlasm::i_sub)
			{
				if (tokens.size() != 3)
					die("Invalid subtraction operation");

				opcode = violet::i_sub;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_fsub)
			{
				if (tokens.size() != 3)
					die("Invalid float subtraction operation");

				opcode = violet::i_fsub;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_xor)
			{
				if (tokens.size() != 3)
					die("Invalid xor operation");

				opcode = violet::i_xor;
				opcode = opcode << 8;

				opcode = opcode | parse_reg(tokens[1]);
				opcode = opcode << 4;
				opcode = opcode | parse_reg(tokens[2]);
				opcode = opcode << 12;

				program.push_back(opcode);
				pc++;
			}
			else if (tokens[0] == vlasm::i_lab)
			{
				//if (tokens.size() < 2)
					//die("Invalid label operation");
			}
			else
			{
				die("Invalid instruction found");
			}
		}

		uint32_t parse_reg(std::string reg_str)
		{
			std::unordered_map<std::string, uint32_t>::const_iterator r = registers.find(reg_str);

			if (r == registers.end()) 
				die("Invalid register");
			
			return r->second;
		}

		void die(const std::string message)
		{
			std::cerr << message << std::endl;

			exit(1);
		}
	}
}

#endif // VLASM_CPP