#include"lab3_data.h"


void main() {
	std::cout << std::boolalpha;

	std::vector<std::string> array;
	header();
	int n = 0;
	std::vector<std::string>alp;  //{ "[]", "{}", "()" };
	changeAlp(&alp, n);
	test_or_user(&n);
	if (n == 1) { filltest(&array); }
	else        { filluser(&array); std::cout << "\n\n";}

	
	std::cout << "NOTE: a pair can only consist of a correct sequence of brackets.	ex. \"[([)]{}\" --> 1 pair\n";
	std::cout << "NOTE: depth only consist of a correct sequence of brackets.		ex. \"[([]) {}\"--> depth:2\n\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~\n\n";
	std::cout << "   string\t\t correct?\tpairs\tdepth\tmore open or closed?\n\n";


	for (int i = 0; i < array.size(); i++) {
		std::string brline = array[i];
		output_data(i, brline, alp);
	}

	std::cout << "~~~ END OF PROGRAM ~~~\n\n";
}
