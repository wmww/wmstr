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
	TEST(endOf("✗abc╢").u, 5);
	
	{
		string a = "π✗ab♛c╢";
		
		Itr i(a);
		
		i.onward(6);
		i.backItUp(4);
		
		TEST(i.u, 1);
		TEST(i.b, 2);
		TEST(i.bNext, 5);
	}
	
	{
		string a = "π✗ab♛c╢";
		
		Itr i(a);
		
		i.onward(100);
		TEST(i.u, 7);
		i.backItUp(100);
		TEST(i.u, -1);
	}
	
	TEST(startsWith("π✗ab♛c╢", "π✗a"), true);
	TEST(startsWith("cπ✗ab♛c╢", "π✗a"), false);
	TEST(endsWith("cπ✗ab♛c╢", "╢"), true);
	TEST(endsWith("cπ✗ab♛c╢", "d"), false);
	
	TEST(endOf("a").u, 1);
	
	TEST(find("cπ✗ab♛c╢", "ab♛").u, 3);
	
	{
		string a = "abc_✗_✗π✗a_✗123";
		
		vector<string> v;
		
		splitBy(v, a, "_✗");
		
		TEST((int)v.size(), 3);
		
		if (v.size() == 3)
		{
			TEST(v[0], "abc");
			TEST(v[1], "π✗a");
			TEST(v[2], "123");
		}
	}
	
	{
		string a = "abc_✗||✗π✗a_✗123||✗nnn_✗";
		
		vector<string> s = {"||✗", "_✗"};
		vector<string> v;
		
		splitBy(v, a, s);
		
		TEST((int)v.size(), 4);
		
		if (v.size() == 4)
		{
			TEST(v[0], "abc");
			TEST(v[1], "π✗a");
			TEST(v[2], "123");
			TEST(v[3], "nnn");
		}
	}
	
	return 0;
}
