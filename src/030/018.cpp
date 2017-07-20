#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iomanip>
using namespace std;

struct binary {
	binary* left;
	binary* right;

	int value;
	int sum;

	binary(const int& v, binary* l = nullptr, binary* r = nullptr) : value(v), left(l), right(r) {
		checksum();
	}
	void checksum() {
		int lvalue = 0, rvalue = 0;
		if (left) {
			lvalue = left->sum;
		}
		if (right) {
			rvalue = right->sum;
		}
		sum = value + max(lvalue, rvalue);
	}
};
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 018 [file]" << endl;
		return 1;
	}
	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	list<binary*> tree;

	int range_from = 0;
	int range_to = 0;
	int index = 0;
	int number = 0;
	int line = 1;
	while (file >> number) {
		cout << setw(2) << setfill(' ') << number << ' ';

		range_from = (line - 2)*(line - 1) / 2;
		range_to = (line - 1)*line / 2;

		binary* left = nullptr;
		binary* right = nullptr;
		if (!tree.empty()) {
			if (index - line >= range_from) {
				auto it = tree.begin();
				advance(it, index - line);
				left = *it;
			}
			if (index - line + 1 < range_to) {
				auto it = tree.begin();
				advance(it, index - line + 1);
				right = *it;
			}
		}
		binary* node = new binary(number, left, right);
		tree.push_back(node);

		++index;
		if (index == (line*(line + 1) / 2)) {
			++line;
			cout << endl;
		}
	}

	file.close();

	int result = 0;
	for (auto it = tree.begin(); it != tree.end(); ++it) {
		result = max(result, (*it)->sum);
		delete *it;
	}

	cout << result << endl;

	return 0;
}