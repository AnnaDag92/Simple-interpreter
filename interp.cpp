#include <iostream>
#include "interp.h"


int if_cond = 0;
int if_cond_true = 0;
std::string line;
std::ifstream myfile("example.txt");
std::vector<variable> vars;
bool is_digit(std::string parsed_line) {
	for (int i = 0; i < parsed_line.size(); ++i) {
		if (parsed_line[i] < 48 || parsed_line[i] > 57) {
			return 0;
		}
	}
	return 1;
}
std::vector<std::string> Parser(std::string Line) {
	std::vector<std::string> tokens;
	std::string str = " ";
	int pos = 0;
	std::string token;
	while ((pos = Line.find(str)) != std::string::npos) {
		token = Line.substr(0, pos);
		if (token != "") {
			tokens.push_back(token);
		}
		if (pos != Line.size() - 1) {
			Line.erase(0, pos + 1);
		}
		else {
			break;
		}
	}
	if (Line != " ") {
		tokens.push_back(Line);
	}
	return tokens;
}
int analyzer(std::vector<std::string> parsed_line) {
	if (parsed_line[parsed_line.size() - 1] != ";") {
		return 0;// error missing ;
	}
	else if ((parsed_line[0] == "set") && parsed_line.size() == 3) {
		declaration(parsed_line);
		return 1; // declaration
	}
	else if ((parsed_line[0] == "set") && (parsed_line.size() == 5) && (parsed_line[2] == "=")) {
		dec_and_ass(parsed_line);
		return 2; // dec. and ass.
	}
	else if ((parsed_line[1] == "=") && parsed_line.size() == 4) {
		assignment(parsed_line);
		return 3; // assignment
	}
	else if ((parsed_line[0] == "set") && (parsed_line[4] == "+") && parsed_line.size() == 7) {
		dec_and_sum(parsed_line);
		return 4; // declaration and sum
	}
	else if ((parsed_line[1] == "=") && (parsed_line[3] == "+") && parsed_line.size() == 6) {
		ass_and_sum(parsed_line);
		return 5; // assignment and sum
	}
	else if ((parsed_line[0] == "set") && (parsed_line[4] == "-") && parsed_line.size() == 7) {
		dec_and_sub(parsed_line);
		return 6; // declaration and sub
	}
	else if ((parsed_line[1] == "=") && (parsed_line[3] == "-") && parsed_line.size() == 6) {
		ass_and_sub(parsed_line);
		return 7; // assignment and sub
	}
	else if ((parsed_line[0] == "set") && (parsed_line[4] == "*") && parsed_line.size() == 7) {
		dec_and_mul(parsed_line);
		return 8; // declaration and mul
	}
	else if ((parsed_line[1] == "=") && (parsed_line[3] == "*") && parsed_line.size() == 6) {
		ass_and_mul(parsed_line);
		return 9; // assignment and mul
	}
	else if ((parsed_line[0] == "set") && (parsed_line[4] == "/") && parsed_line.size() == 7) {
		dec_and_div(parsed_line);
		return 10; // declaration and div
	}
	else if ((parsed_line[1] == "=") && (parsed_line[3] == "/") && parsed_line.size() == 6) {
		ass_and_div(parsed_line);
		return 11; // assignment and div
	}
	else if ((parsed_line[0] == "#")) {
		comment(parsed_line);
		return 12; // comment
	}
	else if ((parsed_line[0] == "print")) {
		print(parsed_line);
		return 13; // print
	}
	else if ((parsed_line[0] == "when") && (parsed_line[3] == ">") && (parsed_line.size() == 6)) {
		if_cond = 1;
		when_greater(parsed_line);
		return 14; // when >
	}
	else if ((parsed_line[0] == "when") && (parsed_line[3] == "<") && (parsed_line.size() == 6)) {
		if_cond = 1;
		when_smaller(parsed_line);
		return 15; // when <
	}
	else if ((parsed_line[0] == "when") && (parsed_line[3] == "==") && (parsed_line.size() == 6)) {
		if_cond = 1;
		when_equal(parsed_line);
		return 16; // when ==
	}
	else if ((parsed_line[0] == "when") && (parsed_line[3] == "!=") && (parsed_line.size() == 6)) {
		if_cond = 1;
		when_not_equal(parsed_line);
		return 17; // when !=
	}

	else if ((parsed_line[0] == "when") && (parsed_line[3] == ">=") && (parsed_line.size() == 6)) {
		if_cond = 1;
		when_greater_equal(parsed_line);
		return 18; // when >=
	}
	else if ((parsed_line[0] == "when") && (parsed_line[3] == "<=") && (parsed_line.size() == 6)) {
		if_cond = 1;
		when_smaller_equal(parsed_line);
		return 16; // when <=
	}
	else if ((parsed_line[0] == "{")) {
		return 17; // {
	}
	else if ((parsed_line[0] == "}")) {
		return 18; // }
	}
	else {
		return 0;
	}
}
void declaration(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[1]) {
			std::cout << "You have already declared this variable" << std::endl;
			return;
		}
	}
	variable new_var;
	new_var.var_name = parsed_line[1];
	new_var.var_value = 0;
	vars.push_back(new_var);
	return;
}
void dec_and_ass(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[1]) {
			std::cout << "You have already declared this variable" << std::endl;
			return;
		}
	}
	variable new_var;
	if (is_digit(parsed_line[3])) {
		new_var.var_name = parsed_line[1];
		new_var.var_value = std::stoi(parsed_line[3]);
		vars.push_back(new_var);
		return;
	}
	else {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_name = parsed_line[1];
				new_var.var_value = vars[j].var_value;
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
}
void assignment(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[0]) {
			if (is_digit(parsed_line[2])) {
				vars[i].var_value = std::stoi(parsed_line[2]);
				return;
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value;
						return;
					}	
				}
			std::cout << "Can't assign invalid value" << std::endl;
			return;
			}
		}
	}
	std::cout << "Uninitialised variable" << std::endl;
	return;
}
void comment(std::vector<std::string> parsed_line) {
	parsed_line.erase(parsed_line.begin(), parsed_line.end());
}
void print(std::vector<std::string> parsed_line) {
	if (parsed_line[1] == "<") {
		for (int i = 2; i < parsed_line.size() - 2; ++i) {
			std::cout << parsed_line[i] << " ";
		}
	}
	else {
		for (int i = 0; i < vars.size(); ++i) {
			if (vars[i].var_name == parsed_line[1]) {
				std::cout << vars[i].var_value << std::endl;
			}
		}
	}

}
void dec_and_sum(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[1]) {
			std::cout << "You have already declared this variable" << std::endl;
			return;
		}
	}
	variable new_var;
	new_var.var_name = parsed_line[1];
	if (is_digit(parsed_line[3]) && is_digit(parsed_line[5])) {
		new_var.var_value = std::stoi(parsed_line[3]) + std::stoi(parsed_line[5]);
		vars.push_back(new_var);
		return;
	}
	else if (is_digit(parsed_line[3])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value = vars[j].var_value + std::stoi(parsed_line[3]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else if (is_digit(parsed_line[5])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value + std::stoi(parsed_line[5]);
				vars.push_back(new_var);
				return;
			}
			else {
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
		}
	}
	else {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value;
			}
		}
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value += vars[j].var_value;
				vars.push_back(new_var);
				return;
			}
		}
	}
}
void ass_and_sum(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[0]) {
			if (is_digit(parsed_line[2]) && is_digit(parsed_line[4])) {
				vars[i].var_value = std::stoi(parsed_line[2]) + std::stoi(parsed_line[4]);
				return;
			}
			else if (is_digit(parsed_line[2])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value = vars[j].var_value + std::stoi(parsed_line[2]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else if (is_digit(parsed_line[4])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value + std::stoi(parsed_line[4]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value;
					}
				}
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value += vars[j].var_value;
						return;
					}
				}
			}
		}
	}
}
void dec_and_sub(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[1]) {
			std::cout << "You have already declared this variable" << std::endl;
			return;
		}
	}
	variable new_var;
	new_var.var_name = parsed_line[1];
	if (is_digit(parsed_line[3]) && is_digit(parsed_line[5])) {
		new_var.var_value = std::stoi(parsed_line[3]) - std::stoi(parsed_line[5]);
		vars.push_back(new_var);
		return;
	}
	else if (is_digit(parsed_line[3])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value = vars[j].var_value - std::stoi(parsed_line[3]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else if (is_digit(parsed_line[5])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value - std::stoi(parsed_line[5]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value;
			}
		}
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value -= vars[j].var_value;
				vars.push_back(new_var);
				return;
			}
		}
	}
}
void ass_and_sub(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[0]) {
			if (is_digit(parsed_line[2]) && is_digit(parsed_line[4])) {
				vars[i].var_value = std::stoi(parsed_line[2]) - std::stoi(parsed_line[4]);
				return;
			}
			else if (is_digit(parsed_line[2])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value = vars[j].var_value - std::stoi(parsed_line[2]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else if (is_digit(parsed_line[4])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value - std::stoi(parsed_line[4]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value;
					}
				}
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value -= vars[j].var_value;
						return;
					}
				}
			}
		}
	}
}
void dec_and_mul(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[1]) {
			std::cout << "You have already declared this variable" << std::endl;
			return;
		}
	}
	variable new_var;
	new_var.var_name = parsed_line[1];
	if (is_digit(parsed_line[3]) && is_digit(parsed_line[5])) {
		new_var.var_value = std::stoi(parsed_line[3]) * std::stoi(parsed_line[5]);
		vars.push_back(new_var);
		return;
	}
	else if (is_digit(parsed_line[3])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value = vars[j].var_value * std::stoi(parsed_line[3]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else if (is_digit(parsed_line[5])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value * std::stoi(parsed_line[5]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value;
			}
		}
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value *= vars[j].var_value;
				vars.push_back(new_var);
				return;
			}
		}
	}
}
void ass_and_mul(std::vector<std::string> parsed_line) {
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[0]) {
			if (is_digit(parsed_line[2]) && is_digit(parsed_line[4])) {
				vars[i].var_value = std::stoi(parsed_line[2]) * std::stoi(parsed_line[4]);
				return;
			}
			else if (is_digit(parsed_line[2])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value = vars[j].var_value * std::stoi(parsed_line[2]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else if (is_digit(parsed_line[4])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value * std::stoi(parsed_line[4]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value;
					}
				}
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value *= vars[j].var_value;
						return;
					}
				}
			}
		}
	}
}
void dec_and_div(std::vector<std::string> parsed_line) {
	if (parsed_line[3] == "0") {
		std::cout << "Zero can not be divisible" << std::endl;
		return;
	}
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[1]) {
			std::cout << "You have already declared this variable" << std::endl;
			return;
		}
	}
	variable new_var;
	new_var.var_name = parsed_line[1];
	if (is_digit(parsed_line[3]) && is_digit(parsed_line[5])) {
		new_var.var_value = std::stoi(parsed_line[3]) / std::stoi(parsed_line[5]);
		vars.push_back(new_var);
		return;
	}
	else if (is_digit(parsed_line[3])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value = vars[j].var_value / std::stoi(parsed_line[3]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else if (is_digit(parsed_line[5])) {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value / std::stoi(parsed_line[5]);
				vars.push_back(new_var);
				return;
			}
		}
		std::cout << "Can't assign an uninitialised variable" << std::endl;
		return;
	}
	else {
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[3]) {
				new_var.var_value = vars[j].var_value;
			}
		}
		for (int j = 0; j < vars.size(); ++j) {
			if (vars[j].var_name == parsed_line[5]) {
				new_var.var_value /= vars[j].var_value;
				vars.push_back(new_var);
				return;
			}
		}
	}
}
void ass_and_div(std::vector<std::string> parsed_line) {
	if (parsed_line[2] == "0") {
		std::cout << "Zero can not be divisible" << std::endl;
		return;
	}
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[0]) {
			if (is_digit(parsed_line[2]) && is_digit(parsed_line[4])) {
				vars[i].var_value = std::stoi(parsed_line[2]) / std::stoi(parsed_line[4]);
				return;
			}
			else if (is_digit(parsed_line[2])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value = vars[j].var_value / std::stoi(parsed_line[2]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else if (is_digit(parsed_line[4])) {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value / std::stoi(parsed_line[4]);
						return;
					}
				}
				std::cout << "Can't assign an uninitialised variable" << std::endl;
				return;
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[2]) {
						vars[i].var_value = vars[j].var_value;
					}

				}
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						vars[i].var_value /= vars[j].var_value;
						return;
					}
				}
			}
		}
	}
}
void when_greater(std::vector<std::string> parsed_line) {
	if_cond = 1;
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[2]) {
			if (is_digit(parsed_line[4])) {
				if (vars[i].var_value > stoi(parsed_line[4])) {
					if_cond_true = 1;
					return;
				}
			}
			else {
				std::cout << "Can" << std::endl;
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						if (vars[i].var_value > vars[j].var_value) {
							if_cond_true = 1;
							return;
						}
					}
				}
			}
		}
	}
}
void when_smaller(std::vector<std::string> parsed_line) {
	if_cond = 1;
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[2]) {
			if (is_digit(parsed_line[4])) {
				if (vars[i].var_value < stoi(parsed_line[4])) {
					if_cond_true = 1;
					return;
				}
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						if (vars[i].var_value < vars[j].var_value) {
							if_cond_true = 1;
							return;
						}
					}
				}
			}
		}
	}
}
void when_equal(std::vector<std::string> parsed_line) {
	if_cond = 1;
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[2]) {
			if (is_digit(parsed_line[4])) {
				if (vars[i].var_value == stoi(parsed_line[4])) {
					if_cond_true = 1;
					return;
				}
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						if (vars[i].var_value == vars[j].var_value) {
							if_cond_true = 1;
							return;
						}
					}
				}
			}
		}
	}
}
void when_not_equal(std::vector<std::string> parsed_line) {
	if_cond = 1;
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[2]) {
			if (is_digit(parsed_line[4])) {
				if (vars[i].var_value != stoi(parsed_line[4])) {
					if_cond_true = 1;
					return;
				}
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						if (vars[i].var_value != vars[j].var_value) {
							if_cond_true = 1;
							return;
						}
					}
				}
			}
		}
	}
}
void when_greater_equal(std::vector<std::string> parsed_line) {
	if_cond = 1;
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[2]) {
			if (is_digit(parsed_line[4])) {
				if (vars[i].var_value >= stoi(parsed_line[4])) {
					if_cond_true = 1;
					return;
				}
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						if (vars[i].var_value >= vars[j].var_value) {
							if_cond_true = 1;
							return;
						}
					}
				}
			}
		}
	}
}
void when_smaller_equal(std::vector<std::string> parsed_line) {
	if_cond = 1;
	for (int i = 0; i < vars.size(); ++i) {
		if (vars[i].var_name == parsed_line[2]) {
			if (is_digit(parsed_line[4])) {
				if (vars[i].var_value <= stoi(parsed_line[4])) {
					if_cond_true = 1;
					return;
				}
			}
			else {
				for (int j = 0; j < vars.size(); ++j) {
					if (vars[j].var_name == parsed_line[4]) {
						if (vars[i].var_value <= vars[j].var_value) {
							if_cond_true = 1;
							return;
						}
					}
				}
			}
		}
	}
}
void Read_from_file() {
	
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			std::vector<std::string> parsed_line;
			getline(myfile, line);
			if (!if_cond) {
				parsed_line = Parser(line);
				analyzer(parsed_line);
			}
			else {
				if (!if_cond_true) {
					std::vector<std::string> skobka;
					skobka.push_back("}");
					parsed_line = Parser(line);
					if (parsed_line != skobka) {
						continue;
					}
					else {
						if_cond_true = 0;
						if_cond = 0;
						continue;
					}
				}
				else {
					if_cond_true = 0;
					if_cond = 0;
					continue;
				}
			}
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}

