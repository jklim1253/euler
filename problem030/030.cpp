#include <iostream>
#include <iomanip>
using namespace std;

template<int N, int E>
struct dp {
	static const int value = N * dp<N, E - 1>::value;
};
template<int N>
struct dp<N,1> {
	static const int value = N;
};
int placeholder(int n) {
	int r = 1;
	while (n--) {
		r *= 10;
	}
	return r;
}
int main(int argc, char* argv[]) {

	int digit[10] = {
		dp<0,5>::value,
		dp<1,5>::value,
		dp<2,5>::value,
		dp<3,5>::value,
		dp<4,5>::value,
		dp<5,5>::value,
		dp<6,5>::value,
		dp<7,5>::value,
		dp<8,5>::value,
		dp<9,5>::value
	};

	// 자릿수에 따른 조합에 참여할 수 있는 범위
	int sum = 0, to = 0;
	for (int d = 1; d < 10; ++d) {

		cout << "------------" << d << "-----------" << endl;
		int i = 0;
		while (digit[i] < placeholder(d) && i < 10) {
			to = i++;
		}
		cout << "max number : " << to << endl;
		auto factorial = [=](int n, int d) {
			int r = 1;
			while (d--) {
				r *= n;
			}
			return r;
		}(to+1, d);
		auto available_max = [&](int n, int d) {
			int r = 0;
			while (d--) {
				r += digit[n];
			}
			return r;
		}(to, d);
		if (available_max >= placeholder(d - 1)) {
			for (i = 2; i < factorial; i++) {
				int check = 0;
				auto number = [&](int order, int place, int limit) {
					int r = 0;
					int unit = 1;
					for (int i = 0; i < place; ++i) {
						check += digit[order%limit];
						if (check >= placeholder(place))
							return 0;

						r += order%limit * unit;
						order /= limit;
						unit *= 10;
					}
					if (check < placeholder(place - 1))
						return 0;

					return r;
				}(i, d, to+1);

				if (number != 0 && check == number) {
					cout << setw(d) << setfill('0') << number << endl;
					sum += number;
				}
			}
		}
		cout << "done" << endl;

		//cin.get();

	}

	cout << "problem 030 : " << sum << endl;

	return 0;
}