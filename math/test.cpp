#include <iostream>
#include <vector>

class someclass {
  int n;
  std::vector<int> value1 = {1, 3, 4, 5, 6};
public:
  void calculate() {
   n = value1.size() / 5;
   std::cout << n;
  }
};

int main() {
  someclass obj;
  obj.calculate();

}
