#include <iostream>
using std::cout;
using std::endl;

#include "wmstr.h"
using namespace wmstr;

void print(int in) {cout << in;}
void print(string in) {cout << "\"" << in << "\"";}

template <typename T>
void unitTest(int lineNum, string code, T first, T second)
{
	if (first == second)
	{
		cout << "✓   " << code << endl;
	}
	else
	{
		cout << endl;
		cout << "✗   " << code << endl;
		cout << "    " << "line " << lineNum << ": '" << code << "' returned ";
		print(first);
		cout << " instead of ";
		print(second);
		cout << endl;
		cout << endl;
	}
}

void unitTest(int lineNum, string code, const char * first, const char * second) {unitTest(lineNum, code, string(first), string(second));}
void unitTest(int lineNum, string code, string first, const char * second) {unitTest(lineNum, code, first, string(second));}
void unitTest(int lineNum, string code, const char * first, string second) {unitTest(lineNum, code, string(first), second);}

#define TEST(a, b) unitTest(__LINE__, #a, a, b)

int main(int argc, char ** argv)
{
	TEST("abc", "abc");
	
	TEST(endOf("abs").u, 3);
	TEST(endOf("abs").b, 3);
	TEST(endOf("_✗_").u, 3);
	TEST(endOf("_✗_").b, 5);
	
	return 0;
}
