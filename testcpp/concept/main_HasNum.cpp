#include <iostream>
#include <string>
#include <concepts>

template <typename T>
concept HasNum = requires(T t) {
  t.m_num;
};

class IntWithNum
{
public:
  int m_num;
};

class Zoo
{
public:
  int m_num;
};

void printNum(HasNum auto number)
{
  std::cout << number.m_num << '\n';
}

int main()
{
  printNum(IntWithNum{5});
  printNum(Zoo{9});
}