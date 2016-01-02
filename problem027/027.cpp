#include <iostream>
using namespace std;

bool isprime(int n) {
	if (n < 2) return false;
	if (n % 2 == 0) return false;

	int i = 3;
	while (i*i <= n) {
		if (n%i == 0)
			return false;
		i+=2;
	}
	return true;
}
int expr(int n, int a, int b) {
	return n*n + a*n + b;
}
int test(int a, int b) {
	int n = 0;
	while (isprime(expr(n, a, b))) {
		n++;
	}
	return n;
}
int main(int argc, char* argv[]) {

	int who[2] = { 0,0 };
	int biggest = 0;
	for (int a = -999; a < 1000; a++) {
		int b = 2;
		while (b < 1000) {
			int r = test(a, b);
			if (biggest < r) {
				biggest = r;
				who[0] = a;
				who[1] = b;
			}
			do {
				if (b == 2) b++;
				else b += 2;
			} while (!isprime(b));
		}
	}

	cout << "who : " << who[0] << ", " << who[1] << " = " << who[0]*who[1] << endl;
	cout << "value : " << biggest << endl;

	return 0;
}