#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	// 1
	// 3 5 7 9
	// 13 17 21 25
	// 
	int size = 1001;

	int biggest_prev = 1;
	int stage = 1;
	int sum = 1;

	while (stage <= (size - 1) / 2) {
		// next number-group start(s) : 2*stage(d) + biggest number of prev number-group(biggest-prev)
		int start_next = 2 * stage + biggest_prev;

		// current number-group is (s+0*d) + (s+1*d) + (s+2*d) + (s+3*d)
		// sum is 4*s + 6*d
		sum += 4 * start_next + 6 * 2 * stage;

		biggest_prev = start_next + 3 * 2 * stage;

		++stage;
	}

	cout << "problem 028 : " << sum << endl;


	return 0;
}