#include <iostream>
#include <dlfcn.h>
#include <string>
#include <vector>

int main()
{
    void *handler = dlopen("libshared.so", RTLD_LAZY);
    if (handler == nullptr)
        std::cout << "error open";
    void (*shared_func)(std::vector<std::string>) = (void (*)(std::vector<std::string>))dlsym(handler, "shared_func");
    if (shared_func == nullptr)
        std::cout << "error dlsym";
    std::cout << shared_func << "\n";
    std::vector<std::string> vec{"zxl", "qwe", "asd"};
    shared_func(vec);

    dlclose(handler);
    //  shared_func();

    dlclose(handler);
}