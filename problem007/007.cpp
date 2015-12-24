#include <iostream>
#include <sstream>
#include <list>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 007 [number]" << endl;
		return 1;
	}
	istringstream is(argv[1]);
	int index;
	is >> index;

	int n = 3;
	list<int> primes;
	primes.push_back(2);
	while (primes.size() < index) {

		bool isprime = true;
		for (auto it = primes.begin(); it != primes.end() && *it <= sqrt(n); ++it) {
			if (n%*it == 0) {
				isprime = false;
				break;
			}
		}
		if (isprime)
			primes.push_back(n);

		n += 2;
	}

	cout << index << " prime is " << primes.back() << endl;

	return 0;
}