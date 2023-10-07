#include <iostream>

int main()
{
#define AAA 0
    std::cout << AAA;
#define AAA 1
    std::cout << AAA;
}