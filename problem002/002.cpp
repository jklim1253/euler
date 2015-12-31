#include <iostream>
#include <sstream>
using namespace std;

/*
 * find the sum of even-valued terms in the Fibonacci sequence.
 *
 */
template<typename T, typename UnaryFunction>
T sum_of_fibo_range(const T& from, const T& to, UnaryFunction& condi) {
	const int size = 3;
	T sum = 0;
	T arr[size] = { 1,2, };
	int index = 0;
	while (arr[index%size] <= to) {
		arr[(index + 2)%size] = arr[(index + 1)%size] + arr[index%size];

		if (arr[index%size] >= from && condi(arr[index%size])) {
			sum += arr[index%size];
		}

		++index;
	}

	return sum;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 002 [limit-number]" << endl;
		return 1;
	}
	istringstream is(argv[1]);
	int limit;
	is >> limit;

	int sum = sum_of_fibo_range(1, limit, [](const int& v) -> bool {
		return (v % 2 == 0);
	});
	cout << "sum of those : " << sum << endl;

	return 0;
}