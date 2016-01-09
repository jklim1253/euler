#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<int, int> factor_type;

factor_type factors(int n) {
	factor_type f;

	for (int i = 2; i*i <= n; ++i) {
		if (n%i == 0) {
			++f[i];
			n = n / i;
			i = 1;
		}
	}
	if (n != 1) {
		++f[n];
	}

	return f;
}
template<typename T>
T power(const T& i, const size_t& e) {
	if (e == 0)
		return 1;
	if (e == 1)
		return i;

	return power(i, e / 2) * power(i, e - e / 2);
}
size_t factors_count(const factor_type& ft) {
	size_t total = 1;
	for (auto it = ft.cbegin(); it != ft.cend(); ++it) {
		total = total*(it->second + 1);
	}

	return total;
}
factor_type::key_type combination(const factor_type& ft, const size_t& idx) {
	size_t total = factors_count(ft);

	size_t index = idx%total;
	factor_type::key_type result = 1;
	auto it = ft.cbegin();
	while (it != ft.cend()) {
		result *= power(it->first, index%(it->second+1));
		index = index / (it->second+1);

		++it;
	}

	return result;
}
int sum_of_factor(const int& n) {

	factor_type f = factors(n);

	int sum = 0;

	size_t fc = factors_count(f) - 1;
	for (size_t i = 0; i < fc; ++i) {
		sum += combination(f, i);
	}

	return sum;
}
int amicable(const int& n) {
	return 0;
}
int main(int argc, char* argv[]) {

	cout << sum_of_factor(220) << endl;
	cout << sum_of_factor(284) << endl;

	vector<int> result(10001, 0);
	for (int i = 1; i <= 10000; ++i) {
		result[i] = sum_of_factor(i);
	}

	int sum = 0;
	for (int i = 1; i <= 10000; ++i) {
		if (result[i] <= 10000 && result[i] > 1) {
			if (result[result[i]] == i && result[i] != i) {
				cout << i << " => " << result[i] << " : ";
				cout << result[i] << " => " << result[result[i]] << endl;
				sum += i + result[i];
				result[i] = 0;
				result[result[i]] = 0;
			}
		}
	}

	cout << "sum of amicable : " << sum << endl;

	return 0;
}