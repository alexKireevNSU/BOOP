#include"stack_calculator.h"
#include <exception>
#include <unordered_map>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
std::vector<double> stack;
std::map<std::string, double> defs;

using namespace stack_calculator;

std::unordered_map<std::string, Command*> commands;

void Pop::doCalc() {
	if (stack.empty())
		throw CommandException("Stack is empty");
	else
		stack.pop_back();
}
void Push::doCalc() {
	stack.push_back(num);
}
void Define::doCalc() {
	defs[name] = num;
}
void Print::doCalc() {
	if (stack.empty())
		throw CommandException("Stack is empty");
	else 
		std::cout << stack.back() << std::endl;
}
void Plus::doCalc() {
	if (stack.size() < 2) throw CommandException("Too few numbers in stack");
	else {
		double a = stack.back();
		stack.pop_back();
		stack.back() += a;
	}
}
void Minus::doCalc() {
	if (stack.size() < 2) throw CommandException("Too few numbers in stack");
	else {
		double a = stack.back();
		stack.pop_back();
		stack.back() = a - stack.back();
	}
}
void Mult::doCalc() {
	if (stack.size() < 2) throw CommandException("Too few numbers in stack");
	else {
		double a = stack.back();
		stack.pop_back();
		stack.back() *= a;
	}
}
void Div::doCalc() {
	if (stack.size() < 2) throw CommandException("Too few numbers in stack");
	else {
		double a = stack.back();
		stack.pop_back();
		stack.back() = a / stack.back();
	}
}
void Sqrt::doCalc() {
	if (stack.empty())
		throw CommandException("Stack is empty");
	else
		stack.back() = sqrt(stack.back());
}

Command* PopFactory::factoryMethod() { return new Pop(); }
Command* PushFactory::factoryMethod() { 
	double num = 0;
	try {
		num = stod(this->num);
	}
	catch (std::exception e) {
		for (const auto& p : defs) {
			if (p.first == this->num) return new Push(p.second);
		}
		throw CommandException("No such defined numbers");
		return nullptr;
	}
	
	return new Push(num);
}
Command* DefineFactory::factoryMethod() {
	double num = 0;
	try {
		num = stod(this->num);
	}
	catch (std::exception e) {
		for (const auto& p : defs) {
			if (p.first == this->num) return new Define(name, p.second);
		}
	}
	return new Define(name, num);
}
Command* PrintFactory::factoryMethod() { return new Print(); }
Command* PlusFactory::factoryMethod() { return new Plus(); }
Command* MinusFactory::factoryMethod() { return new Minus(); }
Command* MultFactory::factoryMethod() { return new Mult(); }
Command* DivFactory::factoryMethod() { return new Div(); }
Command* SqrtFactory::factoryMethod() { return new Sqrt(); }

//std::vector<std::string> stack_calculator::split_string(char* str) {
//	std::vector<std::string> strs;
//	if (str == 0) return strs;
//	for (size_t j = 0; j < strlen(str) + 1; j++) {
//		std::string str_t;
//		for (size_t i = j; i < strlen(str) + 1; i++) {
//			if (str[i] == '\0' || str[i] == '\n') {
//				strs.push_back(str_t);
//				return strs;
//			}
//			if (str[i] != ' ')
//				str_t.push_back(str[i]);
//			else {
//				j = i;
//				break;
//			}
//		}
//		strs.push_back(str_t);
//	}
//	return strs;
//}

Command* get_command(std::vector<std::string> strs) throw() {
	std::unordered_map<std::string, Command*>::const_iterator it = commands.find(strs[0]);
	if (it == commands.end()) {
		if (strs[0] == "+") {
			PlusFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["+"] = c;
			}
			return c;
		}
		if (strs[0] == "-") {
			MinusFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["-"] = c;
			}
			return c;
		}
		if (strs[0] == "*") {
			MultFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["*"] = c;
			}
			return c;
		}
		if (strs[0] == "/") {
			DivFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["/"] = c;
			}
			return c;
		}
		if (strs[0] == "POP") {
			PopFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["POP"] = c;
			}
			return c;
		}
		if (strs[0] == "PUSH") {
			if (strs.size() < 2) {
				throw CommandException("Not enough arguments for push");
				//return nullptr;
			}
			PushFactory f(strs[1]);
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["PUSH"] = c;
			}
			return c;
		}
		if (strs[0] == "SQRT") {
			SqrtFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["SQRT"] = c;
			}
			return c;
		}
		if (strs[0] == "PRINT") {
			PrintFactory f;
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["PRINT"] = c;
			}
			return c;
		}
		if (strs[0] == "DEFINE") {
			if (strs.size() < 3) {
				throw CommandException("Not enough arguments for define");
				//return nullptr;
			}
			DefineFactory f(strs[1], strs[2]);
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["DEFINE"] = c;
			}
			return c;
		}
		throw CommandException("No such command");
	}
	else {
		if (it->first == "DEFINE") {
			if (strs.size() < 3) {
				throw CommandException("Not enough arguments for define");
				//return nullptr;
			}
			DefineFactory f(strs[1], strs[2]);
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["DEFINE"] = c;
			}
			return c;
		}
		if (it->first == "PUSH") {
			if (strs.size() < 2) {
				throw CommandException("Not enough arguments for push");
				//return nullptr;
			}
			PushFactory f(strs[1]);
			Command* c = f.factoryMethod();
			if (c != nullptr) {
				commands["PUSH"] = c;
			}
			return c;
		}
		return it->second;
	}
}
std::vector<std::string> stack_calculator::split_string(std::string str) {
	std::vector<std::string> strs;
	if (str.empty()) return strs;
	for (size_t j = 0; j < str.length() + 1; j++) {
		std::string str_t;
		for (size_t i = j; i < str.length() + 1; i++) {
			if (str[i] == '\0' || str[i] == '\n') {
				strs.push_back(str_t);
				return strs;
			}
			if (str[i] != ' ')
				str_t.push_back(str[i]);
			else {
				j = i;
				break;
			}
		}
		strs.push_back(str_t);
	}
	return strs;
}

void stack_calculator::calculate(std::ifstream& input) {
	//if (input == stdin) std::cout << "Print EXIT to exit from calculator" << std::endl;
	while (!input.eof()) {
		//char buff[100];
		//char* str = fgets(buff, 100, input);
		std::string str;
		std::getline(input, str);
		
		if (str.empty()) continue;
		if (str[0] == '#') continue;
		
		//std::cout << str << std::endl;
		std::vector<std::string> strs = split_string(str);
		if (strs.empty()) continue;
		if (strs[0] == "EXIT") return;
		try {
			Command* c = get_command(strs);
			if (c != nullptr) {
				c->doCalc();
			}
		}
		catch (stack_calculator::CommandException& e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::for_each(commands.begin(), commands.end(), [](std::pair<std::string, Command*> p) {
		delete p.second;
	});
	commands.clear();
	//stack.clear();
	//defs.clear();
}
//void stack_calculator::calculate() {
//	std::cout << "Print STOP to stop the process" << std::endl;
//	while (true) {
//		std::string str;
//		std::getline(std::cin, str);
//		if (str == "STOP") return;
//		std::vector<std::string> strs = split_string(str);
//		if (strs.empty()) continue;
//		if (strs[0] == "+") {
//			PlusFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "-") {
//			MinusFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "*") {
//			MultFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "/") {
//			DivFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "POP") {
//			PopFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "PUSH") {
//			if (strs.size() < 2) throw std::exception("not enough arguments for push");
//
//			PushFactory f(strs[1]);
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "SQRT") {
//			SqrtFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "PRINT") {
//			PrintFactory f;
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//		if (strs[0] == "DEFINE") {
//			if (strs.size() < 3) throw std::exception("not enough arguments for define");
//			DefineFactory f(strs[1], strs[2]);
//			returnf.factoryMethod();
//			c->doCalc();
//			delete c;
//			c = nullptr;
//		}
//	}
//}


bool stack_calculator::stack_is_empty() {
	return stack.empty();
}
bool stack_calculator::defs_is_empty() {
	return defs.empty();
}

std::vector<double> stack_calculator::get_stack() {
	return stack;
}
std::map<std::string, double> stack_calculator::get_defs() {
	return defs;
}

void stack_calculator::clear_stack() {
	stack.clear();
}
void stack_calculator::clear_defs() {
	defs.clear();
}