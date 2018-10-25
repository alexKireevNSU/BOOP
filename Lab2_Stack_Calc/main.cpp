#include <iostream>
#include "gtest/gtest.h"
#include "stack_calculator.h"

#define TESTING

using namespace stack_calculator;
using namespace std;

TEST(Operations, Comments) {
	EXPECT_TRUE(true == true);
}
TEST(Operations, PRINT) {

}
TEST(Operations, PUSH) {

}
TEST(Operations, POP) {

}
TEST(Operations, DEFINE) {

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