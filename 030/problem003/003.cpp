#include <iostream>
#include <sstream>
#include <set>
using namespace std;

template<typename T>
T isprime(const T& N) {
	T sqv = static_cast<T>(sqrt(N));
	for (T i = 2; i <= sqv; ++i) {
		if (N % i == 0)
			return i;
	}

	return N;
}

template<typename T>
class factor {
	T limit;
	set<T> elements;
	void find_elements() {
		T N = limit;
		T element = 1;

		while (N != (element = isprime(N))) {
			N = N / element;
			elements.insert(element);
		}
		elements.insert(element);
	}
public :
	factor(const T& v) : limit(v) {
		find_elements();
	}
	friend ostream& operator << (ostream& os, const factor& ft) {
		for (const T& e : ft.elements) {
			os << e << " ";
		}
		return os;
	}
};

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : 003 [number]" << endl;
		return 1;
	}

	istringstream is(argv[1]);
	unsigned long long input;
	is >> input;

	cout << "factor of " << input << " are : " << endl;
	cout << factor<decltype(input)>(input) << endl;

	return 0;
}