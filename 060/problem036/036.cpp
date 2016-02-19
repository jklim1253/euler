#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string to_binary(int n) {
	string binary;
	while (n > 0) {
		binary.push_back('0'+(n%2));
		n /= 2;
	}
	return binary;
}
int reverse(int n) {
	int r = 0;
	while (n > 0) {
		r *= 10;
		r += n%10;
		n /= 10;
	}
	return r;
}
bool is_palindrome(int n) {
	int rev = reverse(n);
	if (n != rev) {
		return false;
	}
	string binary = to_binary(n);
	string rev_binary = binary;
	reverse(rev_binary.begin(), rev_binary.end());
	if (binary != rev_binary) {
		return false;
	}
	return true;
}
int main() {
	int sum = 0;
	int max_range = 1000000;
	for (int i = 1; i < max_range; i++) {
		if (is_palindrome(i)) {
			sum += i;
			cout << i << "\t" << to_binary(i) << endl;
		}
	}

	cout << "sum of palindrome(1 ~ " << max_range << ") is " << sum << endl;

	return 0;
}
