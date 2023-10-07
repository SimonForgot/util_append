#include <iostream>
#include <string>
#include <vector>
extern "C"
{
    void shared_func(std::vector<std::string> meshNames)
    {
        for (const auto &i : meshNames)
            std::cout << i << " ";
    }
}
