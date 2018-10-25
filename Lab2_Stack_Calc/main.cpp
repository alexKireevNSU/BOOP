#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include"stack_calculator.h"
using namespace stack_calculator;
#define DEV_STAGE
using namespace std;

int main(int argc, char** argv) {
	if (argc > 1) {
		FILE* input;
		errno_t err = fopen_s(&input, argv[1], "r");
		if (err != 0) {
			cout << "error";
			return 0;
		}
		calculate(input);
	}
	else {
		calculate(stdin);
	}
	system("pause");
	return 0;
}