#include <iostream>
#include <vector>
#include <deque>
using namespace std;

/*
 * 어떤 값은 그 값보다 같거나 작은 값의 조합으로만 만들어 질 수 있다.
 *
 * tree 형태로 구성할 수 있고, binary tree가 아니라 
 * 부모 노드가 n일때
 * 자식 노드는 n보다 작거나 같은 수들의 모임인 tree이다.
 * leaf 까지의 합이 n일때 찾은거고,
 * leaf 까지의 합이 n을 넘어서거나, 
 * 제일 작은 값까지 더했는데도 합이 안되면 못 찾은거다.
 *
 * 재귀로 구현했는데.. 재귀의 특성상 주어지는 n 일때 작은 값이 m일 경우
 * n/m 의 재귀의 최대 호출 횟수가 되어, 3000 정도가 되면 오류가 발생할 수도 있다.
 *
 * loop를 이용하는 방법을 다시 구현해봐야겠다.
 */
int make_child(int sum, const vector<int>& v, const size_t& index) {
	// if index is v.size() or sum is over, then no match.
	if (index == v.size() || sum < 0) {
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
