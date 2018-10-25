#include <iostream>
using namespace std;

void calculate(FILE* input) {
	while (true) {
		char buff[100];
		char* str = fgets(buff, 100, input);
		char command[20];
		for (unsigned int i = 0; i < 20; i++) command[i] = 0;
		for (unsigned int i = 0; i < 20; i++) {
			if (str[i] == ' '
				|| str[i] == '\n'
				|| str[i] == '\0') break;
			command[i] = str[i];
		}
		cout << command << endl;
		if (feof(input)) break;
	}
}
void calculate() {
	return;
}

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
		cout << "lold";
	}
	system("pause");
	return 0;
}