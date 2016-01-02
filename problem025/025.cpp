#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<unsigned place>
struct bits {
	// 2^10 => 10^3 : (place/3)*10 => bits count which need represent place digit.
	// unsigned bit count : sizeof(unsigned)*8
	// + 1 : may need one more for reminder bits.
	static const unsigned value = (place / 3) * 10 / (8 * sizeof(unsigned)) + 1;
};

template<unsigned fixed = bits<1000>::value>
class Number {
	static const unsigned MSB = 1 << (sizeof(unsigned) * 8 - 1);
	static const unsigned unit_bits = sizeof(unsigned) * 8;
	static const unsigned base = 10;
	vector<unsigned> value;
public :
	Number(unsigned i = 0) : value(fixed, 0) {
		value[0] = i;
	}
	friend Number operator + (const Number& lhs, const Number& rhs) {

		// per unsigned element, calculate addition using bitwise operator.
		Number carry;
		Number first = lhs;
		Number second = rhs;

		do {
			carry = first & second;

			carry = carry << 1;

			first = first ^ second;
			second = carry;

		} while (carry != 0);

		return first;
	}
	friend Number operator & (const Number& lhs, const Number& rhs) {
		Number AND;
		for (unsigned i = 0; i < AND.value.size(); ++i) {
			AND.value[i] = lhs.value[i] & rhs.value[i];
		}
		return AND;
	}
	friend Number operator | (const Number& lhs, const Number& rhs) {
		Number OR;
		for (unsigned i = 0; i < OR.value.size(); ++i) {
			OR.value[i] = lhs.value[i] | rhs.value[i];
		}
		return OR;
	}
	friend Number operator ^ (const Number& lhs, const Number& rhs) {
		Number XOR;
		for (unsigned i = 0; i < XOR.value.size(); ++i) {
			XOR.value[i] = lhs.value[i] ^ rhs.value[i];
		}
	}
	friend Number operator ~ (const Number& o) {
		Number NOT;
		for (unsigned i = 0; i < NOT.value.size(); ++i) {
			NOT.value[i] = ~o.value[i];
		}
		return NOT;
	}
	friend bool operator == (const Number& lhs, const Number& rhs) {
		bool EQ = true;
		for (unsigned i = 0; i < lhs.value.size(); ++i) {
			if (lhs.value[i] != rhs.value[i]) {
				EQ = false;
				break;
			}
		}

		return EQ;
	}
	friend bool operator != (const Number& lhs, const Number& rhs) {
		return !(lhs == rhs);
	}
	friend Number operator << (const Number& lhs, const int& much) {
		Number SHIFT;

		// shift unit
		unsigned prev;
		int much_outer = much / unit_bits;
		if (much_outer > 0) {
			for (int i = fixed - 1; i > 0; ++i) {
				// shift할 데이터가 존재할 경우
				if (i - much_outer >= 0) {
					prev = lhs.value[i - much_outer];
				}
				// shift할 데이터가 존재하지 않을 경우
				else {
					prev = 0;
				}
				lhs.value[i] = prev;
			}
		}

		// inner unit shift
		int much_inner = much % unit_bits;
		for (int i = lhs.value.size() - 1; i > 0; ++i) {
			// shift할 비트가 있다면
			if (i - much_inner >= 0) {
				prev = (lhs.value[i - 1] & MSB) >> (sizeof(unsigned)*8 - 1);
			}
			// shift할 비트가 없다면
			else {
				prev = 0;
			}

			lhs.value[i] = (lhs.value[i] << much_inner) | prev;
		}
		return SHIFT;
	}
	friend ostream& operator << (ostream& os, const Number& num) {
	}
};

class SimpleUnsignedNumber {
	static const unsigned base = 10;
	string value;
public :
	SimpleUnsignedNumber(unsigned i = 0) {
		if (i == 0) {
			value.push_back('0');
			return;
		}
		while (i > 0) {
			value.push_back(i%base + '0');
			i /= 10;
		}
	}
	SimpleUnsignedNumber(const string& s)
		: value(s.crbegin(), s.crend()) {}
	template<typename InputIter>
	SimpleUnsignedNumber(InputIter Last, InputIter First)
		: value(Last, First) {}
	size_t length() const {
		return value.size();
	}
	friend SimpleUnsignedNumber operator + (const SimpleUnsignedNumber& lhs, const SimpleUnsignedNumber& rhs) {
		string result;
		auto lit = lhs.value.begin();
		auto rit = rhs.value.begin();
		unsigned tmp = 0, carry = 0;
		while (lit != lhs.value.end() || rit != rhs.value.end() || carry != 0) {
			tmp = carry;
			if (lit != lhs.value.end()) {
				tmp += *lit - '0';
				++lit;
			}
			if (rit != rhs.value.end()) {
				tmp += *rit - '0';
				++rit;
			}
			result.push_back(tmp%base + '0');
			carry = tmp / base;
		}
		return SimpleUnsignedNumber(result.begin(), result.end());
	}
	friend ostream& operator << (ostream& os, const SimpleUnsignedNumber& num) {
		auto digit = num.value.rbegin();
		while (digit != num.value.rend()) {
			os.put(*digit);
		}
		return os;
	}
};
int main(int argc, char* argv[]) {
	SimpleUnsignedNumber value[3];
	
	static const unsigned size = 3;
	unsigned index = 0;
	value[0] = 1;
	value[1] = 1;

	while (value[index%size].length() < 1000U) {
		value[(index + 2) % size] = value[(index + 1) % size] + value[index%size];

		++index;
	}

	// index is started on 0, not 1.
	cout << "problem 25 : " << (index + 1) << endl;

	return 0;
}