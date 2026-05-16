#pragma once
#include<vector>
#include<iostream>
#include<string>


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


void cinpillow();
void header();
void output_data(int i, std::string brline, std::vector<std::string>alphabet);


bool pair(char first, char second, std::vector<std::string> alphabet); 
int more(stack brs, std::vector<std::string>alphabet);


void changeAlp(std::vector<std::string>* alphabet, int n);
void test_or_user(int* n);
void filltest(std::vector<std::string>* array_test);
void filluser(std::vector<std::string>* array_test);


bool inAlp(char c, std::vector<std::string>alphabet);
bool isError(char first, char second, std::vector<std::string>alphabet);
bool isClosed(char c, std::vector<std::string>alphabet);


//  main function 
//   |
//   v
std::vector<int> check_brackets(std::string brline, std::vector<std::string>alphabet);
