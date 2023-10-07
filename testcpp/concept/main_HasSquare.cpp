#include <iostream>
#include <string>
#include <concepts>

template <typename T> // 2
concept HasSquare = requires (T t) {
    t.square();
};

class IntWithoutSquare {
public:
  IntWithoutSquare(int num) : m_num(num) {}
private:
  int m_num;
};

class IntWithSquare {
public:
  IntWithSquare(int num) : m_num(num) {}
  int square() {
    return m_num * m_num;
  }
private:
  int m_num;
};


void printSquare(HasSquare auto number) { // 1
  std::cout << number.square() << '\n';
}

int main() {
  //printSquare(IntWithoutSquare{4}); // error: use of function 'void printSquare(auto:11) [with auto:11 = IntWithoutSquare]' with unsatisfied constraints, 
                                    // the required expression 't.square()' is invalid
  printSquare(IntWithSquare{5});
}