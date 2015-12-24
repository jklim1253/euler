#include <iostream>
#include <sstream>
using namespace std;

int fibo(const int& limit) {
	int result = 0;

	int n = 1;
	int n_1 = 2;
	int n_2;

	result += n_1;

	while ((n_2 = n + n_1) <= limit) {
		if (n_2 % 2 == 0)
			result += n_2;
		n = n_1;
		n_1 = n_2;
	}

	return result;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "002 [number]" << endl;
		return 1;
	}

	istringstream is(argv[1]);
	int limit;
	is >> limit;

	cout << "sum of those : " << fibo(limit) << endl;

	return 0;
}