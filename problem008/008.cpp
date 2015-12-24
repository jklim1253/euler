#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

template<typename T, int N>
int multiply(T(&arr)[N]) {
	int r = 1;
	for (int i = 0; i < N; ++i) {
		r = r * arr[i];
	}
	return r;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 008 [filename]" << endl;
		return 1;
	}
	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	const int size = 5;
	int num[size] = { 0, };
	int pos = 0;
	char c;
	int result = 0;
	while (file.get(c).good()) {
		if (!isdigit(c)) continue;
		num[pos%size] = int(c - '0');
		++pos;
		result = max(result, multiply(num));
	}

	cout << "max value : " << result << endl;

	file.close();

	return 0;
}