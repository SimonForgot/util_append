#include<iostream>
#include<string>

using namespace std;


int main()
{
	//C++ will automatically add \0 to the end of "hello"
	const char *cc = "hello";
	string s{cc};
	cout << s;
}