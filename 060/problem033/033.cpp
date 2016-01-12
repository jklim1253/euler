#include <iostream>
#include <list>
#include <algorithm> // __gcd
using namespace std;

// find non-trivial fractions.
/*
   ab     a
  ---- = ---
   bc     c

  분수는 1보다 작아야 한다. -- a < b, a < c

  (10a + b)c = (10b + c)a
  => 10에 대해 풀어보면 ...
  10ac - 10ba = ac - bc
  10(c-b)a = (a-b)c
        (a - b)c      (b - a)c     > 0
  10 = ----------- = ----------         ----- a < c < b
        (c - b)a      (b - c)a     > 0

  a를 상수라고 생각하고 위 식을 b와 c의 함수라고 생각하여 b에 대해 정리하면...
  bc - 10ab = ac - 10ac
  b(c - 10a) = -9ac
          9ac
  b = ---------- < 10 이면서 자연수여야 하므로 9ac%(10a-c) == 0 이여야 한다.
        10a - c
                                              100a
  9ac < 100a - 10c, (9a + 10)c < 100a, c < ---------
                                            9a + 10

  위 조건들을 정리해 보면

  1) a < c < b : a 의 범위는 1 ~ 7

  2) 9ac%(10a-c) == 0

           100a
  3) c < ---------
          9a + 10

  가 되겠다.

  구현해보면...
 */
int main(void) {

	auto A = [](int a, int b, int c)->bool{ return (a < c) && (c < b); };
	auto B = [](int a, int c)->bool{ return ((9*a*c)%(10*a - c) == 0); };
	auto C = [](int a, int c)->int { return (9*a*c)/(10*a - c); };

	list<pair<int,int>> result;
	list<pair<int,int>> solution;
	int a, b, c;
	// find
	for (a = 1; a <= 7; ++a) {
		int max_c = (100*a)/(9*a + 10);
		for (c = a+1; c <= max_c; ++c) {
			if (!B(a,c)) continue;

			b = C(a,c);

			if (!A(a,b,c)) continue;

			result.push_back(make_pair(10*a+b,10*b+c));
			solution.push_back(make_pair(a,c));
		}
	}
	// print
	for (auto& up : result) {
		cout << up.first << ' ';
	}
	cout << endl;
	for (unsigned i = 0; i < result.size(); ++i) {
		cout << "-- ";
	}
	cout << endl;
	for (auto& down : result) {
		cout << down.second << ' ';
	}
	cout << endl;

	// solution.
	int up = 1, down = 1;
	for (auto& fraction : solution) {
		up *= fraction.first;
		down *= fraction.second;
	}

	int g = __gcd(up, down);

	cout << "solution : " << down/g << endl;

	return 0;
}
