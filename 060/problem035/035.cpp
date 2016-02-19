#include <iostream>
using namespace std;

bool is_prime(int n) {
	if (n == 2) return true;
	if (n%2 == 0) return false;
	int i = 3;
	while (i*i <= n) {
		if (n%i == 0) {
			return false;
		}
		i += 2;
	}
	return true;
}
int get_digit_count(int n) {
	int dc = 0;
	while (n > 0) {
		dc++;
		n /= 10;
	}
	return dc;
}
bool is_circular_prime(int n) {
	if (!is_prime(n)) {
		return false;
	}

	int dc = get_digit_count(n);
	int power = 1;
	int loop = dc;
	while (--loop) {
		power *= 10;
	}
	for (int i = 0; i < dc-1; i++) {
		n = (n/10) + (n%10)*power;
		if (!is_prime(n)) {
			return false;
		}
	}

	return true;
}
int main() {

	int count = 0;
	for (int i = 2; i < 1000000; i++) {
		if (is_circular_prime(i)) {
			count++;
			//cout << i << endl;
		}
	}

	cout << "total count of circular prime is " << count << endl;

	return 0;
}
