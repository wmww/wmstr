#include <iostream>
using std::cout;
using std::endl;

#include "wmstr.h"

void unitTest(int lineNum, string code, string first, string second)
{
	if (first == second)
	{
		cout << code << " ✓" << endl;
	}
	else
	{
		cout << code << " ✗" << endl;
		cout << "    " << "line " << lineNum << ": " << code << " returned \"" << first << "\" instead of \"" << second << "\"" << endl;
	}
}

#define TEST(a, b) unitTest(__LINE__, #a, a, b)

int main(int argc, char ** argv)
{
	TEST(string("hay"), "yo");
	
	return 0;
}
