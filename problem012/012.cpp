#include <iostream>
#include <sstream>
#include <map>
using namespace std;

inline int sigma(const int& n) {
	return n*(n + 1) / 2;
}
inline int factors(const int& n) {
	
	map<int, int> factor;
	int N = n;
	while (N != 1) {
		bool isprime = true;
		for (int i = 2; i <= sqrt(N); ++i) {
			if (N%i == 0) {
				++factor[i];
				N = N / i;
				isprime = false;
				break;
			}
		}
		if (isprime) {
			++factor[N];
			N = N / N;
		}
	}
	int result = 1;
	for (auto it = factor.begin(); it != factor.end(); ++it) {
		result = result * (1 + it->second);
	}

	return result;
}
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 012 [number]" << endl;
		return 1;
	}

	istringstream is(argv[1]);
	int limit;
	is >> limit;

	int i = 0;
	while (1) {
		if (factors(sigma(++i)) >= limit)
			break;
	}

	cout << "result : " << sigma(i) << endl;

	return 0;
}