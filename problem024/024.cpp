#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
using namespace std;

int fact(int n) {
	int result = 1;
	while (n > 1) {
		result *= n--;
	}
	return result;
}

// first <= first-index / first-factorial(remain-digit-count)
// second <= (first-index % first-factorial(remain-digit-count)) / second-factorial(remain-digit-count)
// third <= (second-index % second-factorial(remain-digit-count)) / third-factorial(remain-digit-count)
// .... loop
// .... to no remained digit.
void perm(list<int> arr, int index) {
	auto it = arr.begin();
	int factorial = fact(arr.size() - 1);
	advance(it, index / factorial);
	cout << *it;

	arr.erase(it);
	if (arr.size() > 0)
		perm(arr, index % factorial);
}

int main(int argc, char* argv[]) {
	static const int size = 3;
	list<int> arr = { 0,1,2,3,4,5,6,7,8,9 };

	perm(arr, 1000000-1);
	cout << endl;

	return 0;
}