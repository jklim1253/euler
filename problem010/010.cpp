#include <iostream>
#include <sstream>
#include <list>
using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : 010 [number]" << endl;
		return 1;
	}
	istringstream is(argv[1]);
	long long limit;
	is >> limit;

	list<long long> primes;
	primes.push_back(2);
	long long n = 3;
	long long sum = 2;

	while (n <= limit) {
		bool isprime = true;
		for (auto it = primes.begin(); it != primes.end() && *it <= sqrt(n); ++it) {
			if (n%*it == 0) {
				isprime = false;
				break;
			}
		}
		if (isprime) {
			primes.push_back(n);
			sum += n;
		}
		
		n += 2;
	}

	cout << "sum of primes : " << sum << endl;

	return 0;
}