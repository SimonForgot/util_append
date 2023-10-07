#include <iostream>

void shared_func();
void static_func()
{
    std::cout << "static      ";
    shared_func();
}