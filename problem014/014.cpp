#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

inline long long collatz(const long long& n, vector<long long>& depot, const long long& limit) {
	if (n <= limit) {
		if (depot[n] != 0) {
			return depot[n];
		}
		else {
			if (n % 2 == 0) {
				depot[n] = 1 + collatz(n / 2, depot, limit);
			}
			else {
				depot[n] = 1 + collatz(3 * n + 1, depot, limit);
			}
		}
	}
	else {
		if (n % 2 == 0) {
			return 1 + collatz(n / 2, depot, limit);
		}
		else {
			return 1 + collatz(3 * n + 1, depot, limit);
		}
	}

	return depot[n];
}
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 014 [number]" << endl;
		return 1;
	}
	istringstream is(argv[1]);
	long long limit;
	is >> limit;

	vector<long long> depot(limit+1, 0);
	depot[1] = 1;
	long long max_stage = 1;
	long long who = 1;

	for (long long i = 1; i <= limit; ++i) {
		if (max_stage < collatz(i, depot, limit)) {
			max_stage = collatz(i, depot, limit);
			who = i;
		}
	}


	cout << "max stage : " << max_stage << endl;
	cout << "who : " << who << endl;

	return 0;
}