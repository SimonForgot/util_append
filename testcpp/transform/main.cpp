#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int
main ()
{
  vector<float> a{ 1, 2, 3, 4 };
  vector<float> b{ 4, 3, 2, 1 };
  transform (a.begin (), a.end (), b.begin (), a.begin (),
             std::minus<float> ());

  for (auto i : a)
    cout << i << " ";
  cout << "\n";
  for (auto i : b)
    cout << i << " ";
}
