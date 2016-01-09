#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <set>
using namespace std;

/*
	input : a (a_from <= a <= a_to)
			b (b_from <= b <= b_to)

	output : count of value a^b that is different to others.
*/
class Some {
	map<int, int> value;
public :
	Some(int a = 1) {
		init(a);
	}
	void init(int n) {
		value.clear();
		int i = 2;
		while (n != 1) {
			if (n%i == 0) {
				value[i]++;
				n = n / i;
				i = 1;
			}
			++i;
		}
	}
	inline string key() const {
		ostringstream os;
		auto it = value.cbegin();
		while (it != value.cend()) {
			os << it->first << "-" << it->second << ":";
			++it;
		}

		return os.str();
	}
	friend Some operator ^ (const Some& lhs, const int& rhs) {
		Some r = lhs;
		for (auto& e : r.value) {
			e.second *= rhs;
		}
		return r;
	}
	friend ostream& operator << (ostream& os, const Some& o) {
		auto it = o.value.cbegin();
		while (it != o.value.cend()) {
			os << "[" << it->first << "]" << it->second << ",";
			++it;
		}
		return os;
	}
};
int main(int argc, char* argv[]) {
	set<string> unique;

	int duplicate = 0;
	int count = 0;
	for (int a = 2; a <= 100; ++a) {
		Some A(a);
		for (int b = 2; b <= 100; ++b) {
			Some B = A^b;
			auto it = unique.insert(B.key());
			if (!it.second) {
				cout << B << endl;
				cout << a << ":" << b << endl;
				duplicate++;
			}
		}
	}

	cout << "duplicate : " << duplicate << endl;
	cout << "problem 029 : " << unique.size() << endl;

	return 0;
}