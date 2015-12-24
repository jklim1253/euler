#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : 001 [number]" << endl;
		return 1;
	}

	istringstream is(argv[1]);
	int limit;
	is >> limit;

	int sum = 0;
	for (int i = 3; i < limit; ++i) {
		if (i % 3 == 0 || i % 5 == 0)
			sum += i;
	}

	cout << "sum of those : " << sum << endl;

	return 0;
}