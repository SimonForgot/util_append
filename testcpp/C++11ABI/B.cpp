#include <string>
#include <iostream>
extern "C"
{
    void fb(std::string str)
    {
        std::cout << "fb\n";
    }
}
