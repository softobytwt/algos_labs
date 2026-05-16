#include"lab3_data.h"


////// stack functions //////

// these are self explanatory
bool stack::isEmpty() {
	return stack_data.empty();
}

void stack::push(char br) {
	stack_data.push_back(br);
}

char stack::pop() {
	if (not isEmpty()) {
		char b = stack_data.back();
		stack_data.pop_back();
		return b;
	}
	else
	{
		std::cout<<"\nWARNING: stack.pop() operation not completed, stack is empty\n";
	}
}

char stack::peek() {
	if (not isEmpty()) { return stack_data.back(); }
	else { std::cout <<"\nstack is empty\n"; }
}

int stack::size() {
	return stack_data.size();
}





//////////  other  //////////




//				cinpillow just cleans up invalid user input (if there is any)
void cinpillow() {
	std::cin.clear();
	std::cin.ignore(1000, '\n');
}





//				basically just text
void header() {
	std::cout << "choose alphabet:\n1. [], (), {}\n2. [], (), {}, <>\n3. ()\n";
}





//				pair checks if first and second are a pair			ex. () -> true, (] -> false
bool pair(char first, char second, std::vector<std::string> alphabet) {
	for (int i = 0; i < alphabet.size(); i++) {
		if (first == alphabet[i][0] && second == alphabet[i][1]) {return 1;}
	}
	return 0; 
}





//				more checks if there are more open or closed brackets	ex.  []()-> 0(even),   ()( -> 1(open),   []} -> 2(closed)
int more(stack brs, std::vector<std::string>alphabet) {
	int lastsize = brs.size();

	int open = 0;
	int closed = 0;
	for (int i = 0; i < lastsize; i++) {
		char br = brs.peek();
		if (isClosed(br, alphabet))closed++;
		else open++;
		brs.pop();
	}

	if (open == closed) return 0;
	if (open > closed) return 1;
	return 2;
}





//				starter function only used once. changeAlp changes alphabet depending on user choice
void changeAlp(std::vector<std::string>*alphabet, int n) {
	std::cout << "input the number of your choice: ";
	std::cin >> n;
	cinpillow();

	(*alphabet).push_back("()");
	if (not (n == 3)) { (*alphabet).push_back("[]"); (*alphabet).push_back("{}"); }
	if (n == 2) { (*alphabet).push_back("<>"); }
	
	if((n<1) || (n>3)){ std::cout << "\nWARNING: invalid choice number.\nyour alphabet is set to default (1)\n"; }
	std::cout << "\n\n";
}




//				inAlp checks if c is in alphabet			ex. inAlp('4', alp) -> false,     inAlp('[', alp) -> true
bool inAlp(char c, std::vector<std::string>alphabet) {       // returns whether c is a symbol in the alphabet //
	for (int i = 0; i < alphabet.size(); i++) {
		for (int j = 0; j < alphabet[i].size(); j++) {
			if (c == alphabet[i][j]) return true;
		}
	}
	return false;
}




//				checks if bracket sequence is correct + counts pairs + uses more(...) + finds depth
std::vector<int> check_brackets(std::string brline, std::vector<std::string>alphabet) {
	std::vector<int> data = { 0, 0, 0, 0 };   
	/////      data = [bracket check(0), count pairs(1), more "(" or ")"/ eql(2), depth(3)]

	stack brackets_st;    

	int lastpopped = 0;
	char temporaryC = 'a';
	for (int i = 0; i < brline.size(); i++) {
		if (not inAlp(brline[i], alphabet)) { continue; }
		brackets_st.push(brline[i]);
		

		if (brackets_st.size() != 1) {
			if (pair(temporaryC, brackets_st.peek(), alphabet)) {
				data[1]++;		// note: it considers a pair only correctly placed brackets
				brackets_st.pop();
				//if (data[3] < brackets_st.size()) data[3] = brackets_st.size();
				brackets_st.pop();
				lastpopped++;
				if (data[3] < lastpopped)data[3] = lastpopped;
			}
			else {
				lastpopped = 0;
				if (isError(temporaryC, brackets_st.peek(), alphabet)) {/*break; */}
			}
		}
		else { 
			lastpopped = 0;
			if (isClosed(brackets_st.peek(), alphabet));/*break;*/
		}
		if (not brackets_st.isEmpty()) { temporaryC = brackets_st.peek(); }
	}


	data[0] = brackets_st.isEmpty();
	data[2] = more(brackets_st, alphabet);
	return data;
}





//				fills up an array with test strings
void filltest(std::vector<std::string> *array_test) {
	(*array_test).push_back("()[]{}");
	(*array_test).push_back("([)]");
	(*array_test).push_back("a + (b * c)");
	(*array_test).push_back("if (a[2] > b)");
	(*array_test).push_back(") [](");
	(*array_test).push_back("{}([<])");
	(*array_test).push_back("<><[]");
	(*array_test).push_back("seal: (:3 u )3");
	(*array_test).push_back("no brackets..");
	(*array_test).push_back(" ");
}





void filluser(std::vector<std::string> *array_test) {
	int arraylen = 0;
	std::cout << "input amount of strings: ";
	std::cin >> arraylen;
	cinpillow();
	if (arraylen <= 0) {
		std::cout << "WARNING: invalid amount.\namount is set to default (1)\n"; arraylen = 1;
	}

	for (int i = 0; i < arraylen; i++) {
		std::cout << i + 1 << ". bracket string: ";
		std::string temp;
		std::getline(std::cin, temp);
		(*array_test).push_back(temp);
	}
}





void test_or_user(int* n) {
	std::cout << "choose one option:\n1.	use test bracket strings\n2.	input user bracket string(s)\n";
	std::cout << "input the number of your choice: ";
	std::cin >> *n;
	cinpillow();
	if ((*n != 1) && (*n != 2)) { std::cout << "WARNING:invalid choice number.\nyour choice is set to default (1)\n"; *n = 1; }
	std::cout << "\n\n";
}





// self explanatory
void output_data(int i, std::string brline, std::vector<std::string>alphabet) {
	std::vector<int> brdata = check_brackets(brline, alphabet);

	std::cout << i + 1 << ". \"" << brline << "\"";
	if (brline.size() < 16)std::cout << "\t";
	if (brline.size() < 8)std::cout << "\t";   // tabbing here to line them all up neatly
	if (brline.size() < 3)std::cout << "\t";   // there is probably a cleaner way to do this but im too tiredddd i want a cheburek
	std::cout << " -> " << bool(brdata[0]) << "\t";
	std::cout << brdata[1] << "\t";
	std::cout << brdata[3] << "\t";
	switch (brdata[2]) {
	case 0:
		std::cout << "=\n";
		break;
	case 1:
		std::cout << "open\n";
		break;
	case 2:
		std::cout << "closed\n";
		break;
	};
}
