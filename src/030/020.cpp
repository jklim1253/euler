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

int main(int argc, char* argv[]) {

	Number n("1");
	Number result("1");

	for (int i = 0; i < 100; ++i) {
		result = result * n;

		n = n + Number("1");
	}

	cout << result << endl;
	cout << result.sum_of_index() << endl;

	return 0;
}