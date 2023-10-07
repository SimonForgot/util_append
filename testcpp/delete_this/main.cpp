#include <iostream>

struct A
{
    virtual void func(){
        std::cout << "func A\n";
    }
    void f()
    {
        //result : func B
        //this means "this" point to the real object
        this->func();
        // delete this;
    }

    virtual ~A() { std::cout << "AAAAAA\n"; };
};

struct B : public A
{
    void func()override
    {
        std::cout << "func B\n";
    }
    ~B() { std::cout << "BBBBB\n"; }
};

int main()
{
    auto p = new B();
    p->f();
    while (1)
    {
    }
}