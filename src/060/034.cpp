#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
using namespace std;

template<int N>
struct factorial {
	static const int value = N*factorial<N-1>::value;
};
template<>
struct factorial<1> {
	static const int value = 1;
};
template<typename T, T condition>
struct if_true {
	static constexpr T value = (true == condition);
};
template<int N>
struct digit_count {
	static const int value = 1 + digit_count<N/10>::value;
};
template<>
struct digit_count<0> {
	static const int value = 0;
};

int get_digit_count(int n) {
	int r = 0;
	while (n > 0) {
		n /= 10;
		++r;
	}
	return r;
}
int main(void) {
	// factorial value : 1 ~ 9
	vector<int> fac = {
		1,
		factorial<1>::value,
		factorial<2>::value,
		factorial<3>::value,
		factorial<4>::value,
		factorial<5>::value,
		factorial<6>::value,
		factorial<7>::value,
		factorial<8>::value,
		factorial<9>::value
	};
	// 팩토리얼의 자릿수.
	vector<int> dcount = {
		1,
		digit_count<factorial<1>::value>::value,
		digit_count<factorial<2>::value>::value,
		digit_count<factorial<3>::value>::value,
		digit_count<factorial<4>::value>::value,
		digit_count<factorial<5>::value>::value,
		digit_count<factorial<6>::value>::value,
		digit_count<factorial<7>::value>::value,
		digit_count<factorial<8>::value>::value,
		digit_count<factorial<9>::value>::value
	};

	cout << "factorial value(0~9):" << endl;
	cout << "====================" << endl;
	for (auto& i : fac) {
		cout << i << endl;
	}
	cout << "====================" << endl;
	cout << "digit count of factorial value(0~9):" << endl;
	cout << "====================" << endl;
	for (auto& i : dcount) {
		cout << i << endl;
	}
	cout << "====================" << endl;

	auto is_curious = [=](int n)->bool {
		int sum = 0;
		int value = n;

		while (value > 0) {
			sum += fac[value%10];
			value = static_cast<int>(value/10);
		}

		return (sum == n);
	};

	auto max_of_digit = [](int dc)->int {
		int value = 0;
		while (dc--) {
			value *= 10;
			value += 9;
		}
		return value;
	};

	auto find_max_curious = [=]()->int {
		int dc = 1; // digit count
		int big = fac[9];
		while (big*dc > max_of_digit(dc)) {
			dc++;
		}
		return big*dc;
	};
	int max_value = find_max_curious();
	cout << "max value of range to check : " << max_value << endl;

	int sum_of_curious = 0;
	for (int i = 3; i < max_value; i++) {
		if (is_curious(i)) {
			sum_of_curious += i;
			cout << i << endl;
		}
	}

	cout << "sum of curious number is " << sum_of_curious << endl;

	return 0;
}
