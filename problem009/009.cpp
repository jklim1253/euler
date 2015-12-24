#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	int a, b, c;
	//a + b + c = 1000;
	//a < b < c;
	//a*a + b*b = c*c;
	bool found = false;
	int alpha = 1;
	while (!found) {
		for (int beta = 1; beta <= alpha; ++beta) {
			if ((1000 - 2 * alpha - beta) % 3 == 0) {
				a = (1000 - 2 * alpha - beta) / 3;
				b = a + alpha;
				c = b + beta;

				if (a*a + b*b == c*c) {
					found = true;
					break;
				}
			}
		}

		if (found)
			break;

		++alpha;
	}

	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "c : " << c << endl;
	cout << "a x b x c : " << (a*b*c) << endl;

	return 0;
}