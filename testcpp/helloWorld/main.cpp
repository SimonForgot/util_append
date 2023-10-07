#include <iostream>
#include <set>
#include <string>

using namespace std;
int main()
{
    set<string> st{"fill", "default", "key"};
    for (auto i : st)
        std::cout << i << " ";
}
