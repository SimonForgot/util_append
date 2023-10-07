#include <iostream>
#include <test.h>

//comments below come from Project cortex file Export.h

// When compiling with `-fvisibility=hidden` with GCC or Clang, we run into
// problems when including 3rd party headers that don't define symbol
// visibility. Because they don't explicitly assign default visibility to
// anything, such headers end up inheriting hidden visibility for _everything_.
// This is particularly problematic if we wish to build template classes around
// those 3rd party types, because if they are hidden, GCC will force our
// class to be hidden too, no matter how we declare it. For instance,
// we would be unable to export `TypedData<Imath::V2f>`. We use these macros
// to push/pop default visibility around such problematic includes.

//This is true
//run [./build.sh c] will cause 
///usr/bin/ld: CMakeFiles/attribute_visibility_exe.dir/main.cpp.o: in function `main':
//main.cpp:(.text.startup+0x9): undefined reference to `test()'

//check it with :
//nm -CD build/libattribute_visibility_lib.so

int main()
{
    auto temp = test();
    std::cout << "Main\n";
}