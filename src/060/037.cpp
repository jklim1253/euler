/*
소수 3797에는 왼쪽부터 자리수를 하나씩 없애거나 (3797, 797, 97, 7) 오른쪽부터 없애도 (3797, 379, 37, 3) 모두 소수가 되는 성질이 있습니다.
이런 성질을 가진 소수는 단 11개만이 존재합니다. 이것을 모두 찾아서 합을 구하세요.
(참고: 2, 3, 5, 7은 제외합니다)
 */
#include <iostream>
using namespace std;

bool is_prime(int n) {
	//cout << "is_prime " << n << endl;
	if (n < 2) return false;
	if (n == 2) return true;
	if (n%2 == 0) return false;
	int i = 3;
	while (i*i <= n) {
		if (n%i == 0) return false;
		i += 2;
	}
	return true;
}
int get_digit_count(int n) {
	int dc = 0;
	while (n > 0) {
		dc++;
		n /= 10;
	}
	return dc;
}
int int_power(int n) {
	int r = 1;
	while (--n) {
		r *= 10;
	}
	return r;
}
int truncate_right(int n) {
	return n/10;
}
int truncate_left(int n) {
	return n%int_power(get_digit_count(n));
}
bool is_truncatable_prime(int n) {
	if (!is_prime(n)) return false;
	int dc = get_digit_count(n);
	if (dc == 1) return false;
	int tr = n;
	int tl = n;
	for (int i = 0; i < dc-1; i++) {
		tr = truncate_right(tr);
		tl = truncate_left(tl);
		if (!is_prime(tr) || !is_prime(tl)) return false;
	}
	return true;
}

int main() {
	int count = 0;
	int sum = 0;
	int n = 1;
	//while (count != 11) {
	while (1) {
		if (is_truncatable_prime(n)) {
			cout << n << endl;
			count++;
			sum += n;
			cout << "current count : " << count << ", and sum is " << sum << endl;
		}
		//cout << n << " current count : " << count << endl;
		n++;
	}

	return 0;
}
