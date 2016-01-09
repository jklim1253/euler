#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

inline int score_of_name(const string& name) {
	int result = 0;
	auto it = name.cbegin();
	while (it != name.cend()) {
		result += *it++ - 'A' + 1;
	}
	return result;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage : 022 [file]" << endl;
		return 1;
	}
	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found" << endl;
		return 2;
	}

	// read file contents, save memory with calculated values.
	list<string> names;
	const char onoff = '"';
	bool word = false;
	char c;
	while (file.get(c).good()) {
		if (c == onoff) {
			word = !word;
			if (word) {
				names.push_back(string());
			}
		}
		else if (word) {
			names.rbegin()->append(1, c);
		}
	}

	cout << "name count : " << names.size() << endl;

	names.sort();

	for (int i = 937; i < 939; ++i) {
		auto it = names.begin();
		advance(it, i);
		cout << i << " : " << *it << endl;
		cout << "score : " << score_of_name(*it) << endl;
	}

	int sum = 0;
	int index = 1;
	for (auto it = names.begin(); it != names.end(); ++it) {
		sum += score_of_name(*it) * index++;
	}

	cout << "problem solution is " << sum << endl;

	return 0;
}