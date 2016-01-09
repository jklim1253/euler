#include <iostream>
#include <string>
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
	size_t length() const {
		return number.size();
	}
	size_t sum_of_index() const {
		size_t result = 0;
		auto it = number.cbegin();
		while (it != number.cend()) {
			result += *it++ - '0';
		}
		return result;
	}
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
	friend Number operator * (const Number& lhs, const Number& rhs) {
		Number result;
		auto lit = lhs.number.begin();
		while (lit != lhs.number.end()) {

			string middle;

			int pos = lit - lhs.number.begin();
			while (pos--) {
				middle.push_back('0');
			}

			int tmp = 0;
			int upper = 0;
			auto rit = rhs.number.begin();
			while (rit != rhs.number.end() || upper != 0) {
				tmp = upper;
				if (rit != rhs.number.end()) {
					tmp += (*rit - '0') * (*lit - '0');
					++rit;
				}

				middle.push_back('0' + (tmp % 10));
				upper = tmp / 10;
			}

			++lit;

			result = result + Number(middle.begin(), middle.end());
		}

		return result;
	}
	friend ostream& operator << (ostream& os, const Number& o) {
		for (auto it = o.number.rbegin(); it != o.number.rend(); ++it) {
			os.put(*it);
		}
		return os;
	}
};

Number power(const Number& n, const int& e) {
	if (e == 0)
		return Number("1");
	if (e == 1)
		return n;

	return power(n, e / 2) * power(n, e - e / 2);
}
int main(int argc, char* argv[]) {

	Number a("134");
	Number b("4");

	cout << (a*b) << endl;
	cout << power(Number("2"), 15) << endl;
	cout << power(Number("2"), 15).sum_of_index() << endl;
	cout << power(Number("2"), 1000) << endl;
	cout << power(Number("2"), 1000).sum_of_index() << endl;

	cin.get();

	return 0;
}