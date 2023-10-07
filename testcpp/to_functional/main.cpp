#include <iostream>
#include <functional>

using namespace std;

void func(float x)
{
    std::cout << "func1\n";
}
void func2(float x)
{
    std::cout << "func2\n";
}
int main()
{
    std::function<std::remove_pointer_t<decltype(func)>> p{func2};
    p(2);
}
