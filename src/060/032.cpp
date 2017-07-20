#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

/*
 * n-digits * m-digits = (n+m-1)-over-digits.
 * n + m + n + m - 1 = 9
 * n + m = 5
 * n : 1, m : 4
 * n : 2, m : 3
 *
 */
int main(void) {
	vector<int> d = {1,2,3,4,5,6,7,8,9};

	//d[0]*(d[1]*1000 + d[2]*100 + d[3]*10 + d[4]) == d[5]*1000 + d[6]*100 + d[7]*10 + d[8]
	auto _14_checker = [](const vector<int>& d)->int{
		int one = d[0]*d[4];
		int ten = d[0]*d[3] + one/10;
		int hundred = d[0]*d[2] + ten/10;
		int thousand = d[0]*d[1] + hundred/10;

		bool R = (one%10 == d[8]) && 
				(ten%10 == d[7]) && 
				(hundred%10 == d[6]) &&
				(thousand%10 == d[5] && thousand/10 == 0);
		if (R)
			return (d[5]*1000 + d[6]*100 + d[7]*10 + d[8]);

		return 0;
	};
	// (d[0]*10 + d[1])*(d[2]*100 + d[3]*10 + d[4]) == d[5]*1000 + d[6]*100 + d[7]*10 + d[8]
	auto _23_checker = [](const vector<int>& d)->int{
		int one = d[1]*d[4];
		int ten = d[1]*d[3] + d[0]*d[4] + one/10;
		int hundred = d[1]*d[2] + d[0]*d[3] + ten/10;
		int thousand = d[0]*d[2] + hundred/10;

		bool R = (one%10 == d[8]) && 
				(ten%10 == d[7]) && 
				(hundred%10 == d[6]) && 
				(thousand%10 == d[5] && thousand/10 == 0);
		if (R)
			return (d[5]*1000 + d[6]*100 + d[7]*10 + d[8]);
		return 0;
	};
	
	std::set<int> sum;
	do {
		int v = 0;
		if ((v = _14_checker(d))) {
			for (auto& e : d) {
				cout << e << ' ';
			}
			cout << endl;
		}
		sum.insert(v);
		if ((v = _23_checker(d))) {
			for (auto& e : d) {
				cout << e << ' ';
			}
			cout << endl;
		}
		sum.insert(v);
	} while (std::next_permutation(d.begin(), d.end()));

	int result = 0;
	for (auto& v : sum) {
		result += v;
	}

	cout << result << endl;

	return 0;
}
