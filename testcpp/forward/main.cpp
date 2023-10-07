// https://zhuanlan.zhihu.com/p/50816420
#include <iostream>
using std::cout;
using std::endl;
template <typename T>
void func(T &param)
{
    cout << "传入的是左值" << endl;
}
template <typename T>
void func(T &&param)
{
    cout << "传入的是右值" << endl;
}

// 万能引用虽然即可以接受左值，又可以接受右值。但是在该函数体内，它被认为是左值，所以需要完美转发。
template <typename T>
void warp(T &&param)
{

    // 引用折叠，简单来说就是只有形参和实参都是右值，才是右值。可以理解为 &&& -> &
    // forward 简单实现版：
    // 不论T是&还是&&，param都将会是&
    /*
    template<typename T>
    T&& forward(T &param)
    {
        // 这样就实现了左值转完还是左值，右值转完还是右值
        return static_cast<T&&>(param);
    }
    */

    // 可以&，被认为是左值！
    &param;

    func(std::forward<T>(param));

    // decltype这种lambda表达式也可用
    // func(std::forward<decltype(param)>(param));

    // func(param);
}

/*
template <typename T = void>
void f()
{
    "字符" = 2233;
}
*/

int main()
{
    int num = 2019;
    warp(num);
    warp(2019);
    return 0;
}