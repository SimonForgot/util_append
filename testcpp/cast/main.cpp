#include <iostream>
#include <string>

using namespace std;

struct A
{
    virtual void f()
    {
        std::cout << "HHH\n";
    };
};

struct B : public A
{
    void f()
    {
        std::cout << "child\n";
    }
};

struct C : public A
{
    C(){}
    C(B& b){}
};

int main()
{
    B b;
    A a;
    C c;
    A *pa = &a;
    B *pb = &b;
    C *pc = &c;

    //compile ok
    C temp = static_cast<C>(b);
    if (1)
    {
        std::cout << "OK\n";
        //pc->f();
    }
    else
        std::cout << "NOO\n";
}
//result: static_cast is a cast that happens in compile time,compiler should know how to cast it.
//for example line 21 C(B& b){},this makes B can be convert to C
//dynamic_cast is more safe and can only be used for inherate classes pointer type cast,it is designed for polymorphism