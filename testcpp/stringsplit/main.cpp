#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> stringSplit(const std::string &str, char delim)
{
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        if (!item.empty())
        {
            elems.push_back(item);
        }
    }
    return elems;
}

int main()
{
    std::string str = "RGBA_";
    std::vector<std::string> aov_name_substr = stringSplit(str, '_');
    for (auto i : aov_name_substr)
    {
        std::cout << i << "\n";
    }
}
