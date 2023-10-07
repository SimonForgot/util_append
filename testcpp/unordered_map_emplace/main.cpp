#include<iostream>
#include<unordered_map>

int main()
{
     std::unordered_map<std::string, int> mp;
     mp.emplace("qwe",123);
     mp.emplace("qwer",999);
     std::cout << mp["qwer"]<<"\n";
}