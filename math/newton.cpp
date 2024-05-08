#include <iostream>
#include <vector>

class newton {
int i, j, fact, n;
double inputX, theQ, theNewton, multiplyN, sum;
std::vector<double> x = {1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11}; // array of x
std::vector<double> y = {0.04879, 0.058269, 0.067659 ,0.076961, 0.086178, 0.09531, 0.10436}; // array of y
public:

  void calculate() {
    std::cout << "Enter Interpolation Point: ";
    std::cin >> inputX;
    n = x.size();
    float deltaY[n][n]; //creating deltaY matrix
    // calculate finite values and fill into deltaY matrix
    for(i = 0; i < n; ++i) {
      for(j = 0; j < n - i; ++j) {
        if (i == 0)
        deltaY[i][j] = y[j+1] - y[j];
        else if (i > 0)
        deltaY[i][j] = deltaY[i-1][j+1] - deltaY[i-1][j];
      }
    }
    // print the table of finite values
    n--;
    std::cout << "\nTable of finite values is: \n";
    for(i = 0; i < n; i++) {
      std::cout << '\n';
      for(j = 0; j < n - i; j++) {
        std::cout << deltaY[i][j] << '\t';
      }
    }
    // theQ is q, sum is answer, multiplyN is a temporary value
    theQ = (inputX - x[0]) / (x[1] - x[0]);
    sum = y[0];
    multiplyN = 1;
    std::cout << "\n\ntheQ is " << theQ << std::endl;

    // start calculating sum
    for(i = 1; i < n; i++) {
        multiplyN *= (theQ - i + 1) / i;
        theNewton = multiplyN  * deltaY[i-1][0];
        sum += theNewton;
        std::cout << "multiplyN is " << multiplyN << std::endl;
        std::cout << "theNewton is " << theNewton << std::endl;
        std::cout << "sum is " << sum << std::endl;
        std::cout << '\n';
    }
    // print answer
    std::cout << "For x = " << inputX << " answer is " << sum << "\n\n";
  }
};

int main() {
  newton obj;
  obj.calculate();
  return 0;
}
