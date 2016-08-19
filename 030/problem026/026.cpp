#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class UnitFraction {
	static const unsigned default_precision = 0;
	unsigned _numerator;
	unsigned _denominator;
	size_t _precision;
	bool _recurring_cycle;
	size_t _cycle_size;
	size_t _cycle_start;
public :
	UnitFraction(const unsigned& deno) 
		: _numerator(1),
		  _denominator(deno),
		  _precision(default_precision),
		  _recurring_cycle(false),
		  _cycle_size(0),
		  _cycle_start(0)
	{
		find_recurring_cycle();
	}
	size_t precision() const {
		return _precision;
	}
	size_t precision(size_t preci) {
		_precision = preci;
		return _precision;
	}
	size_t cycle_size() const {
		return _cycle_size;
	}
	void find_recurring_cycle() {
		unsigned nume = _numerator;
		unsigned deno = _denominator;

		unsigned min_length = [](unsigned n) {
			unsigned r = 0;
			while (n > 0) {
				++r;
				n /= 10;
			}
			return r;
		}(deno);

		string record;

		do {
			nume *= 10;

			unsigned divisor = nume / deno;
			record.push_back(divisor + '0');
			if (find_pattern(record, min_length)) {
				_recurring_cycle = true;
				break;
			}

			nume = nume % deno;
		} while (nume != 0);
	}
	bool find_pattern(const string& record, const unsigned& min_length) {
		if (record.size() < min_length*2)
			return false;

		auto target_start = record.cend();
		advance(target_start, -int(min_length));
		string target(target_start, record.cend());

		auto it = record.find(target);
		if (it == string::npos || it == record.size() - min_length) {
			return false;
		}

		_cycle_start = it;
		_cycle_size = record.size() - min_length - it;

		return true;
	}
	friend ostream& operator << (ostream& os, const UnitFraction& uf) {
		unsigned numerator = uf._numerator;
		unsigned denominator = uf._denominator;
		size_t precision = max(uf._cycle_start + uf._cycle_size*2, uf._precision);

		os.put('0' + (numerator/denominator));
		os.put('.');

		numerator = numerator % denominator;

		do {
			numerator *= 10;

			os.put((numerator / denominator) + '0');
			if (precision > 0) --precision;

			numerator = numerator % denominator;

			// numerator 가 0이면 종료.
			// recurrying_cycle 이 참일 경우에는 precision 이 0이 될때까지 지속.
			// recurrying_cycle 이 거짓일 경우에는 precision 값을 검사하지 않는다.
		} while (numerator != 0 && (!uf._recurring_cycle || (uf._recurring_cycle && precision != 0)));

		if (uf._recurring_cycle && precision > 0) {
			while (precision--) {
				os.put('0');
			}
		}

		return os;
	}
};
int main(int argc, char* argv[]) {

	for (unsigned i = 1; i < 10; ++i) {
		UnitFraction a(i);

		cout << i << "(" << a.cycle_size() << ") : " << a << endl;
	}

	unsigned who = 0;
	size_t longest = 0;
	for (unsigned i = 1; i < 1000 + 1; ++i) {
		UnitFraction a(i);
		if (longest < a.cycle_size()) {
			who = i;
			longest = a.cycle_size();
		}
	}

	cout << "problem 026, denominator having longest recurring cycle is " << who << endl;
	cout << "that value is " << longest << endl;

	return 0;
}
