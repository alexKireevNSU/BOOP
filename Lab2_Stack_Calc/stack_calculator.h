#pragma once
#include<vector>
#include<iostream>
#include<unordered_map>
#include<map>
#include<string>
#include<math.h>
#include <exception>
namespace stack_calculator {


	class Command {
	public:
		virtual void doCalc() = 0;
		virtual ~Command() {}
	};
	class Pop : public Command {
	public:
		void doCalc();
	};
	class Push : public Command {
	private:
		double num;
	public:
		Push(double num) : num(num) {}
		void doCalc();
	};
	class Define : public Command {
		std::string name;
		double num;
	public:
		Define(std::string name, double num) : name(name), num(num) {}
		void doCalc();
	};
	class Print : public Command {
	public:
		void doCalc();
	};
	class Plus : public Command {
	public:
		void doCalc();
	};
	class Minus : public Command {
	public:
		void doCalc();
	};
	class Mult : public Command {
	public:
		void doCalc();
	};
	class Div : public Command {
	public:
		void doCalc();
	};
	class Sqrt : public Command {
	public:
		void doCalc();

	};

	class Factory {
	public:
		virtual Command* factoryMethod() = 0;
		virtual ~Factory(){}
	};
	class PopFactory : public Factory {
	public:
		Command* factoryMethod();
	};
	class PushFactory : public Factory {
	private:
		std::string num;
	public:
		PushFactory(std::string num) : num(num) {}
		Command* factoryMethod();
	};
	class DefineFactory : public Factory {
	private:
		std::string name;
		std::string num;
	public:
		DefineFactory(std::string name, std::string num) : name(name), num(num) {}
		Command* factoryMethod();
	};
	class PrintFactory : public Factory {
	public:
		Command* factoryMethod();
	};
	class PlusFactory : public Factory {
	public:
		Command* factoryMethod();
	};
	class MinusFactory : public Factory {
	public:
		Command* factoryMethod();
	};
	class MultFactory : public Factory {
	public:
		Command* factoryMethod();
	};
	class DivFactory : public Factory {
	public:
		Command* factoryMethod();
	};
	class SqrtFactory : public Factory {
	public:
		Command* factoryMethod();
	};

	//std::vector<std::string> split_string(char* str);
	std::vector<std::string> split_string(std::string str);
	void calculate(std::ifstream& input);


	bool stack_is_empty();
	bool defs_is_empty();
	std::vector<double> get_stack();
	std::map<std::string, double> get_defs();
	void clear_stack();
	void clear_defs();

	class CommandException : public std::exception {
	private:
		std::string message;
	public:
		CommandException(std::string message) : message(message) { }
		std::string what() {
			return this->message;
		}
	};
}
