#include <iostream>
#include <vector>

class lagrange {
	int i, j, n;
	std::vector<float> x = {0.27, 0.93, 1.46, 2.11, 2.87};
	std::vector<float> y = {2.60, 2.43, 2.06, 0.25, -2.60};
	float Elagrange, inputX, polynomL, multiplyL;
public:
	void calculate(int n) {
			std::cout << "Enter Interpolation Point: ";
			std::cin >> inputX;
			n = x.size();
			for(i = 0; i < n; ++i)
			{
				multiplyL = 1;
				polynomL = 1;
				for(j = 0; j < n; ++j)
				{
					if (i != j)
					{
						multiplyL = multiplyL * (inputX - x[j]) / (x[i] - x[j]);
						std::cout << multiplyL << std::endl;
						polynomL *= multiplyL;
					}
				}
				std::cout << "\n\npolynom["<< i << "] is " <<  polynomL << std::endl;
				std::cout << '\n';
				Elagrange = Elagrange + multiplyL * func[i];
			}

		std::cout << "Answer is: " << Elagrange;
	}
};

int main() {
	lagrange l1;
	l1.calculate();
	return 0;

}
