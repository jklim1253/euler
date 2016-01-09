#include <iostream>
using namespace std;

template<int N, int M>
struct road {
	static const long long value = road<N - 1, M>::value
		+ road<N, M - 1>::value;
};
template<int N>
struct road<0, N> {
	static const long long value = 1;
};
template<int N>
struct road<N, 0> {
	static const long long value = 1;
};

int main(int argc, char* argv[]) {

	cout << road<20, 20>::value << endl;

	return 0;
}