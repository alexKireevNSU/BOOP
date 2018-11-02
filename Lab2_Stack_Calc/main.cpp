#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "stack_calculator.h"

#define TESTING

using namespace stack_calculator;
using namespace std;

TEST(Operations, Comments) {
	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/commets_test.txt";
	//ofstream test_input;
	//test_input.open(test_filename, fstream::out);
	//for (size_t i = 0; i < 1000000; i++) {
	//	test_input << "#" << endl;
	//}
	//for (size_t i = 0; i < 500000; i++) {
	//	test_input << "#abracadabra" << endl;
	//}
	//test_input.close();
	//cout << endl << "ready" << endl;

	ifstream input(test_filename);
	calculate(input);
	input.close();

	EXPECT_TRUE(stack_is_empty() && defs_is_empty());
}
TEST(Operations, PUSH) {
	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/push_test.txt";
	//ofstream test_input;
	//test_input.open(test_filename, fstream::out);
	//for (size_t i = 0; i < 1000000; i++) {
	//	test_input << "PUSH " << i << endl;
	//}
	//test_input.close();
	//cout << endl << "ready" << endl;
	//
	ifstream input(test_filename);
	calculate(input);
	input.close();


	EXPECT_FALSE(stack_is_empty());
	EXPECT_TRUE(defs_is_empty());
	vector<double> stack = get_stack();
	//cout << endl << stack.size() << endl;
	EXPECT_TRUE(stack.size() == 1000000);
	
	for (size_t i = 0; i < stack.size(); i++) {
		EXPECT_TRUE(stack[i] == i);
	}
	clear_stack();
	clear_defs();
}
TEST(Operations, POP) {
	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/pop_test.txt";
	//ofstream test_input;
	//test_input.open(test_filename, fstream::out);
	//for (size_t i = 0; i < 1000000; i++) {
	//	test_input << "PUSH " << i << endl;
	//}
	//for (size_t i = 0; i < 1000000; i++) {
	//	test_input << "POP" << endl;
	//}
	//test_input.close();
	
	ifstream input(test_filename);
	calculate(input);
	input.close();
	
	EXPECT_TRUE(get_stack().empty());
}

string gen_random(const int len) {
	static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";

	string s;

	for (int i = 0; i < len; ++i) {
		s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
	}

	return s;
}

TEST(Operations, DEFINE) {
	clear_defs();
	clear_stack();

	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/define_test.txt";
	/*ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 1000000; i++) {
		test_input << "DEFINE " << gen_random(5) << " " << i << endl;
	}

	test_input.close();*/

	ifstream input(test_filename);
	calculate(input);
	input.close();

	auto defs = get_defs();
	EXPECT_TRUE(defs.size() == 959304);

	
}
TEST(Operations, PLUS) {
	clear_defs();
	clear_stack();

	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/plus_test.txt";
	ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 500001; i++) {
		test_input << "PUSH " << 1 << endl;
	}
	for (size_t i = 0; i < 500000; i++) {
		test_input << "+" << endl;
	}

	test_input.close();

	ifstream input(test_filename);
	calculate(input);
	input.close();

	auto stack = get_stack();
	EXPECT_TRUE(stack[0] == 500001);
}
TEST(Operations, MINUS) {
	clear_defs();
	clear_stack();

	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/minus_test.txt";
	ofstream test_input;
	test_input.open(test_filename, fstream::out);
	
	for (size_t i = 0; i < 500000; i++) {
		test_input << "PUSH " << 1 << endl;
	}
	test_input << "PUSH " << 0 << endl;
	for (size_t i = 0; i < 500000; i++) {
		test_input << "-" << endl;
	}


	test_input.close();

	ifstream input(test_filename);
	calculate(input);
	input.close();

	auto stack = get_stack();
	EXPECT_TRUE(stack[0] == -500000);
}
TEST(Operations, MULTIPLICATION) {
	clear_defs();
	clear_stack();

	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/mult_test.txt";
	ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 500000; i++) {
		test_input << "PUSH " << 1.01 << endl;
	}
	for (size_t i = 0; i < 499999; i++) {
		test_input << "*" << endl;
	}

	test_input.close();

	ifstream input(test_filename);
	calculate(input);
	input.close();

	auto stack = get_stack();
	EXPECT_TRUE(stack[0] == pow(1.01, 500000));
}
TEST(Operations, DIVISION) {
	clear_defs();
	clear_stack();

	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/div_test.txt";
	ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 100; i++) {
		test_input << "PUSH " << "10" << endl;
	}
	test_input << "PUSH " << "1.e+100" << endl;
	for (size_t i = 0; i < 100; i++) {
		test_input << "/" << endl;
	}

	test_input.close();

	ifstream input(test_filename);
	calculate(input);
	input.close();

	auto stack = get_stack();
	EXPECT_TRUE(stack[0] <= 1.0 + 0.1 && stack[0] >= 1.0 - 0.1);
}
TEST(Operations, SQRT) {
	clear_defs();
	clear_stack();

	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/sqrt_test.txt";
	ofstream test_input;
	test_input.open(test_filename, fstream::out);
	test_input << "PUSH " << "1.e+128" << endl;
	for (size_t i = 0; i < 7; i++) {
		test_input << "SQRT" << endl;
	}

	test_input.close();

	ifstream input(test_filename);
	calculate(input);
	input.close();

	auto stack = get_stack();
	EXPECT_TRUE(stack[0] == 10);
}

int main(int argc, char** argv) {
#ifdef TESTING // Tests
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
#else
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
	/*const char* path = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/in.txt";
	
	ifstream input(path);
	calculate(input);
	input.close();
	auto defs = get_defs();
	for_each(defs.begin(), defs.end(), [](pair <std::string, double> p) {
		cout << p.first << " " << p.second << endl;
	});*/

#endif

	system("pause");
	return 0;
}