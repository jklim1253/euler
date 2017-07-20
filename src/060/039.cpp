#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

template<typename First, typename Second, typename Third>
struct Triple {
	First first;
	Second second;
	Third third;
	Triple(const First& a, const Second& b, const Third& c) : first(a), second(b), third(c) {}

	friend bool operator < (const Triple<First,Second,Third>& lhs, const Triple<First,Second,Third>& rhs) {
		if (lhs.first < rhs.first) return true;
		else if (lhs.first > rhs.first) return false;

		if (lhs.second < rhs.second) return true;
		else if (lhs.second > rhs.second) return false;

		if (lhs.third < rhs.third) return true;

		return false;
	}
	bool operator == (const Triple& o) {
		return (first == o.first && second == o.second && third == o.third);
	}
	bool operator != (const Triple& o) {
		return !(*this == o);
	}
	bool operator > (const Triple& o) {
		return !(*this < o) && !(*this == o);
	}
};

template<typename First, typename Second, typename Third>
Triple<First,Second,Third> make_triple(const First& a, const Second& b, const Third& c) {
	return Triple<First,Second,Third>(a,b,c);
};

void sort_asc(int& a, int& b, int& c) {
	if (a > b) {
		swap(a, b);
	}
	if (a > c) {
		swap(a, c);
	}
	if (b > c) {
		swap(b, c);
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage : test [range]" << endl;
		return 1;
	}
	int input_zine = 0;
	istringstream iss(argv[1]);
	iss >> input_zine;

	int range_zine = input_zine + 1;

	vector<int> depot(range_zine, 0);
	for (int i = 1; i < range_zine; i++) {
		if (i*i < range_zine) {
			depot[i*i] = i;
		}
	}

	size_t max_count = 0;
	int max_input = 0;
	for (int input = 3; input < input_zine; input++) {

		set<Triple<int,int,int>> result;
		// a + b + c = input
		// aa + bb = cc
		// c = a + diff
		// aa + bb = aa + 2a*diff + diff*diff
		// bb = 2a*diff + diff*diff
		for (int a = 3; a < input/2; a++) {
			for (int diff = 1; a + diff < input/2; diff++) {
				int c = a + diff;

				int bb = 2*a*diff + diff*diff;
				if (bb >= input) break;
				if (depot[bb] == 0) continue;

				int b = depot[bb];

				int unit = a + b + c;

				if (input%unit != 0) continue;

				int amplifier = input/unit;

				int tmp[3] = {a, b, c};
				sort_asc(tmp[0], tmp[1], tmp[2]);
				result.insert(make_triple(tmp[0]*amplifier, tmp[1]*amplifier, tmp[2]*amplifier));
			}
		}

		if (result.size() == 0) continue;

		if (result.size() > max_count) {
			max_count = result.size();
			max_input = input;

			cout << "count(" << max_input << ") : " << max_count << endl;
			for (auto it = result.begin(); it != result.end(); it++) {
				cout << "\tFound : " << it->first << ", " << it->second << ", " << it->third << endl;
			}
		}

	}

	return 0;
}
