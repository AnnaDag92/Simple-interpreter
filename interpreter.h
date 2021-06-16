#pragma once
#include <fstream>
#include <string>
#include "interp.h"
#include <vector>

void Read_from_file();
void declaration(std::vector<std::string> parsed_line);
void dec_and_ass(std::vector<std::string> parsed_line);
void dec_and_sum(std::vector<std::string> parsed_line);
void ass_and_sum(std::vector<std::string> parsed_line);
void dec_and_sub(std::vector<std::string> parsed_line);
void ass_and_sub(std::vector<std::string> parsed_line);
void dec_and_mul(std::vector<std::string> parsed_line);
void ass_and_mul(std::vector<std::string> parsed_line);
void dec_and_div(std::vector<std::string> parsed_line);
void ass_and_div(std::vector<std::string> parsed_line);
void assignment(std::vector<std::string> parsed_line);
void when_greater(std::vector<std::string> parsed_line);
void when_smaller(std::vector<std::string> parsed_line);
void when_equal(std::vector<std::string> parsed_line);
void when_not_equal(std::vector<std::string> parsed_line);
void when_greater_equal(std::vector<std::string> parsed_line);
void when_smaller_equal(std::vector<std::string> parsed_line);
void comment(std::vector<std::string> parsed_line);
void print(std::vector<std::string> parsed_line);
void when_body(std::ifstream& myfile,std::string line, std::vector<std::string> parsed_line);
struct variable {
	std::string var_name;
	int var_value;
};
bool is_digit(std::string str);
std::vector<std::string> Parser(std::string Line);
int analyzer(std::vector<std::string> parsed_line);
