
#include <iostream>
#include <string>

void fa(std::string str);
extern "C" void fb(std::string str);
int main()
{
     fb("sssss");
     fa("dd");
}