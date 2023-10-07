#include <iostream>
using namespace std;

//
class bit_field
{
public:
    bool a : 1;
    bool a1 : 1;
    bool a2 : 1;
    bool a3 : 1;
    bool a4 : 1;
    bool a5 : 1;
    bool a6 : 1;
    bool a7 : 1;


};
int main()
{
    cout << sizeof(bit_field)<<"\n";
    cout<<sizeof(bool);
}