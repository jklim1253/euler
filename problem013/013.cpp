#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Number {
private :
	string number;
public :
	Number() : number("0") {}
	Number(const Number& o) : number(o.number) {}
	Number(const string& num) : number(num.rbegin(), num.rend()) {}
	template<typename Iter>
	Number(Iter Last, Iter First) : number(Last, First) {}
	friend Number operator + (const Number& lhs, const Number& rhs) {
		int tmp = 0;
		int upper = 0;
		string result;
		auto lit = lhs.number.begin();
		auto rit = rhs.number.begin();
		while (lit != lhs.number.end() || rit != rhs.number.end() || upper != 0) {
			tmp = upper;
			if (lit != lhs.number.end()) {
				tmp += *lit - '0';
				++lit;
			}
			if (rit != rhs.number.end()) {
				tmp += *rit - '0';
				++rit;
			}
			result.push_back('0' + (tmp % 10));
			upper = tmp / 10;
		}

		return Number(result.begin(), result.end());
	}
	friend ostream& operator << (ostream& os, const Number& o) {
		for (auto it = o.number.rbegin(); it != o.number.rend(); ++it) {
			os.put(*it);
		}
		return os;
	}
};
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 013 [file]" << endl;
		return 1;
	}
	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	Number result;
	string number;
	while (file >> number) {
		cout << number << endl;
		result = result + Number(number);
	}

	cout << "result : " << result << endl;

	file.close();

	return 0;
}