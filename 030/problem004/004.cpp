#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

template<typename T>
bool palindrome(const T& n) {
	T reverse = 0;
	T N = n;
	while (N > 0) {
		reverse = reverse * 10 + (N % 10);
		N = N / 10;
	}
	return (reverse == n);
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cerr << "Usage : 004 [number] [number]" << endl;
		return 1;
	}
	int from, to;
	istringstream is(string(argv[1]) + " " + argv[2]);
	is >> from >> to;

	cout << from << " ~ " << to << endl;

	int result = 0;
	for (int i = from; i < to; ++i) {
		for (int j = from; j < to; ++j) {
			if (palindrome(i*j))
				result = max(result, i*j);
		}
	}
	cout << "max palindrome : " << result << endl;

	return 0;
}