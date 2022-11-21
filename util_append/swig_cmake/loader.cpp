#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h>

void run(std::vector<std::string> meshNames)
{
    void *handler = dlopen("deformerDetector_backend.so", RTLD_NOW);
    
    if (handler == nullptr)
    {
        std::cout << "error dlopen";
        return;
    }

    void (*main_run)(std::vector<std::string>) = (void (*)(std::vector<std::string>))dlsym(handler, "main_run");
    if (main_run == nullptr)
    {
        std::cout << "error dlsym";
        return;
    }

    main_run(meshNames);
    dlclose(handler);
}