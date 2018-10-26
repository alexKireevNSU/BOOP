#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "stack_calculator.h"

#define TESTING

using namespace stack_calculator;
using namespace std;

TEST(Operations, Comments) {
	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/commets_test.txt";
	/*ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 1000000; i++) {
		test_input << "#" << endl;
	}
	for (size_t i = 0; i < 500000; i++) {
		test_input << "#abracadabra" << endl;
	}
	test_input.close();
	cout << "ready";*/
	FILE* input;
	errno_t err = fopen_s(&input, test_filename, "r");
	if (err != 0) {
		cout << "error";
	}
	calculate(input);
	fclose(input);
	EXPECT_TRUE(stack_is_empty() && defs_is_empty());
}
TEST(Operations, PUSH) {
	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/push_test.txt";
	/*ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 1000000; i++) {
		test_input << "PUSH " << i << endl;
	}
	test_input.close();
	cout << "ready";*/
	FILE* input;
	errno_t err = fopen_s(&input, test_filename, "r");
	if (err != 0) {
		cout << "error";
	}
	calculate(input);
	fclose(input);
	EXPECT_FALSE(stack_is_empty());
	EXPECT_TRUE(defs_is_empty());
	vector<double> stack = get_stack();
	EXPECT_TRUE(stack.size() == 1000000);
	for (size_t i = 0; i < stack.size(); i++) {
		EXPECT_TRUE(stack[i] == i);
	}
}
TEST(Operations, POP) {
	const char* test_filename = "C:/Users/goodaman/source/repos/BOOP/Lab2_Stack_Calc/pop_test.txt";
	ofstream test_input;
	test_input.open(test_filename, fstream::out);
	for (size_t i = 0; i < 1000000; i++) {
		test_input << "POP" << endl;
	}
	test_input.close();
	cout << "ready";
	FILE* input;
	errno_t err = fopen_s(&input, test_filename, "r");
	if (err != 0) {
		cout << "error";
	}
	calculate(input);
	fclose(input);
	EXPECT_TRUE(get_stack().empty());
}
TEST(Operations, DEFINE) {
	clear_defs();
	clear_stack();
	
}
TEST(Operations, PLUS) {

}
TEST(Operations, MINUS) {

}
TEST(Operations, MULTIPLICATION) {

}
TEST(Operations, DIVISION) {

}
TEST(Operations, SQRT) {

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
#endif

	system("pause");
	return 0;
}