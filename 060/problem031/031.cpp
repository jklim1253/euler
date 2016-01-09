#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int make_child(int sum, const vector<int>& v, const size_t& index) {
	// if index is v.size(), then no match.
	if (index == v.size()) {
		return 0;
	}
	else if (sum < 0) {
		return 0;
	}
	// if sum is 0, match found.
	else if (sum == 0) {
		return 1;
	}

	return make_child(sum - v[index], v, index) + 
			make_child(sum, v, index+1);
}
int main(void) {
	//vector<int> money = {200,100,50,20,10,5,2,1};
	vector<int> money = {200,100,50,20,10,5,2,1};
	deque<int> children;

	cout << make_child(200, money, 0) << endl;

	return 0;
}
