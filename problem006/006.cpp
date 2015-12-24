#include <iostream>
#include <sstream>
using namespace std;

int sum_of_square(const int& from, const int& to) {
	int result = 0;
	for (int i = from; i <= to; ++i)
		result += i*i;
	return result;
}
int square_of_sum(const int& from, const int& to) {
	int result = 0;
	for (int i = from; i <= to; ++i)
		result += i;
	return result*result;
}
int difference_of_them(const int& from, const int& to) {
	return square_of_sum(from, to) - sum_of_square(from, to);
}
int main(int argc, char* argv[]) {

	if (argc != 3) {
		cerr << "Usage : 006 [number] [number]" << endl;
		return 1;
	}
	istringstream is(string(argv[1]) + " " + argv[2]);
	int from, to;
	is >> from >> to;

	cout << "result : " << difference_of_them(from, to) << endl;

	return 0;
}