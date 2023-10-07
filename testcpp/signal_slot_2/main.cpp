#include <iostream>

#include "signal.h"
#include "slot.h"

int main()
{
    signal<int> mySignal;
    slot<int> mySlot([](int input)
                     { std::cout << "We received: " << input << std::endl; });
    mySignal.connect(mySlot);

    std::cout << "Emitting signal" << std::endl;
    mySignal.emit(5);
    return 0;
}