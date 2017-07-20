#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
using namespace std;

// find pandigital

string concatenated_product_of(int k, int limit) {
	ostringstream oss;

	int i = 1;
	do {
		oss << (k * i);
	} while (++i <= limit);

	return oss.str();
}

bool is_pandigital(const string& s) {
	if (s.length() != 9) {
		return false;
	}

	bitset<9> check;
	check.set();
	string buffer(s.cbegin(), s.cend());
	for (string::iterator c = buffer.begin(); c != buffer.end(); c++) {
		if (*c - '0' < 0) return false;
		if (!check[*c - '0' - 1]) return false;
		check[*c - '0' - 1] = false;
	}

	return true;
}

int main(void) {

	cout << concatenated_product_of(192, 4) << endl;

	cout << is_pandigital(concatenated_product_of(192, 4)) << endl;

	string max("1"), candidate;
	for (int target = 1; target < 10000; target++) {
		for (int i = 2; i < 10; i++) {
			if (is_pandigital(candidate = concatenated_product_of(target, i))) {
				cout << "target : " << target << " * (1 ~ " << i << ") = " << concatenated_product_of(target, i) << endl;
				if (max < candidate) {
					max = candidate;
				}
			}
		}
	}

	cout << "max value is " << max << endl;
	return 0;
}
