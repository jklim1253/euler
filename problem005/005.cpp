#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

map<int, int> find_factor(const int& n) {
	map<int, int> factors;
	int N = n;
	int i = 2;
	while (N != 1) {
		if (N%i == 0) {
			++factors[i];
			N = N / i;
			i = 2;
		}
		else if (i > sqrt(N)) {
			++factors[N];
			break;
		}
		else {
			++i;
		}
	}
	return factors;
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cerr << "Usage : 005 [number] [number]" << endl;
		return 1;
	}
	istringstream is(string(argv[1]) + " " + argv[2]);
	int from, to;
	is >> from >> to;

	map<int, int> collection;
	for (int i = from; i <= to; ++i) {
		map<int, int> factors = find_factor(i);
		for (auto it = factors.begin(); it != factors.end(); ++it) {
			collection[it->first] = max(collection[it->first], factors[it->first]);
		}
	}

	int result = 1;
	for (auto it = collection.begin(); it != collection.end(); ++it) {
		result = result*pow(it->first, it->second);
	}

	cout << "result : " << result << endl;

	return 0;
}