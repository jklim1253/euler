#include <iostream>
#include <sstream>
using namespace std;

/*
 * find the sum of all the multiples of 3 or 5 below limit.
 *
 */
template<typename T>
inline bool dividable(const T& target, const T& arg) {
	return (target%arg == 0);
}
template<typename T, typename First, typename... Rest>
inline bool dividable(const T& target, const First& first, const Rest&... args) {
	return dividable(target, first) || dividable(target, args...);
}
template<typename T, typename... Arguments>
T sum_of_multiples(const T& limit, const Arguments&... args) {
	T sum = 0;
	for (T i = 1; i <= limit; ++i) {
		if (dividable(i, args...)) {
			sum += i;
			cout << i << ' ';
		}
	}
	cout << endl;
	return sum;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 001 [limit-number]" << endl;
		return 1;
	}

	istringstream is(argv[1]);
	int limit;
	is >> limit;

	int sum = sum_of_multiples(limit, 3, 5);

	cout << "sum of those : " << sum << endl;

	return 0;
}
