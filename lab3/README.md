# лабораторная работа 3 (проверка выражений - stack)
# Бакаринова Софья Андреевна ИДБ-25-02
### описание:
Проверить корректность скобочной последовательности.

### обязательная часть:
Реализовать:
- функцию проверки строки
- поддержку (), [], {}
- ВарЧасть7: определить максимальную глубину вложенных скобок

### дополнительная часть:
кроме обязательной части я решила также реализовать:
- ВарЧасть1: добавить поддержку <>
- ВарЧасть3: подсчитать количество пар
- ВарЧасть4: проверять только круглые скобки ()
- ВарЧасть5: проверять строку и игнорировать все символы, кроме скобок
- ВарЧасть6: вывести каких скобок больше: открывающихся, закрывающихся, ровно
- ВарЧасть10: проверка нескольких строк подряд


### стек реализовывался через динамический массив

## 1. реализация стека
lab3_data.h:
```
class stack {
	std::vector<char>stack_data;
public:
	stack() {};
	bool isEmpty();
	void push(char br);
	char pop();
	char peek();
	int size();
};
```
lab3_data.cpp:
```
bool stack::isEmpty() { return stack_data.empty();}

void stack::push(char br) { stack_data.push_back(br); }

char stack::pop() {
	if (not isEmpty()) {
		char b = stack_data.back();
		stack_data.pop_back();
		return b;
	}
	else{ std::cout<<"\nWARNING: stack.pop() operation not completed, stack is empty\n";}
}

char stack::peek() {
	if (not isEmpty()) { return stack_data.back(); }
	else { std::cout <<"\nstack is empty\n"; }
}

int stack::size() {return stack_data.size();}


```
## 2. основная функция 

возвращает динамический массив: 
- [корректность, кол-во пар, открывающих/закрывающих больше, глубина]

  
функция check_brackets(строка, алфавит):
1. создает стек
2. вставляет в него элемент из строки
3. если stack.size()<2:    lastpopped=0 (lastpopped считает, на сколько глубоко идут данные вложенные скобки)
4. иначе:                проверяет, являются ли temporaryC и stack.peek()  парой
5. если пара:           pairs++ (т.е. data[1]++) и два раза stack.pop() - избавляемся от пары, lastpopped++; (иначе обнуляем ластпоппед)
6. также здесь сравниваем значение depth (data[3]) с lastpopped (lastpopped считает, на сколько глубоко идут данные вложенные скобки)
7. если стек не пустой, кладем в temporaryC последний элемент через stack.peek()

когда строка закончилась, если стек стал пустым - строка корректна, иначе - нет
также функция more выполняет задание ВарЧасть6 (больше открывающих или закрывающих)

lab3_data.cpp:
```
std::vector<int> check_brackets(std::string brline, std::vector<std::string>alphabet) {
	std::vector<int> data = { 0, 0, 0, 0 };  
	stack brackets_st;    
	int lastpopped = 0;
	char temporaryC = 'a';

	for (int i = 0; i < brline.size(); i++) {          //  <---  main loop 
		if (not inAlp(brline[i], alphabet)) { continue; } // <--- if current character is not a bracket: goes to the next char
		brackets_st.push(brline[i]);
		

		if (brackets_st.size() != 1) {
			if (pair(temporaryC, brackets_st.peek(), alphabet)) {
				data[1]++;		// note: it considers a pair only correctly placed brackets
				brackets_st.pop();
				brackets_st.pop();
				lastpopped++;
				if (data[3] < lastpopped)data[3] = lastpopped;
			}
			else {lastpopped = 0;}
		}
		else { lastpopped = 0;}

		if (not brackets_st.isEmpty()) { temporaryC = brackets_st.peek(); }
	}

	data[0] = brackets_st.isEmpty();
	data[2] = more(brackets_st, alphabet);
	return data;
}

```

## 2. алфавит
используется в большинстве функций

алфавит является массивом строк, каждая из которых - пара скобок

alp = ["()", "{}", "[]"]

алфавит нужен для: 
- ВарЧасть1 (<>)
- ВарЧасть4 (только () )
- ВарЧасть5 (при любом из данных алфавитов будут игнорироваться все символы, кроме скобок)

lab3_main.cpp:
```
std::vector<std::string>alp;  //{ "[]", "{}", "()" };
changeAlp(&alp, n);
```
lab3_data.cpp:

1.
```
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

```
2.
```
bool inAlp(char c, std::vector<std::string>alphabet) {       // returns whether c is a symbol in the alphabet //
	for (int i = 0; i < alphabet.size(); i++) {
		for (int j = 0; j < alphabet[i].size(); j++) {
			if (c == alphabet[i][j]) return true;
		}
	}
	return false;
}
```

