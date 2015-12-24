#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : 011 [file]" << endl;
		return 1;
	}
	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	int arr[20][20] = { 0, };

	for (int y = 0; y < 20; ++y) {
		for (int x = 0; x < 20; ++x) {
			file >> arr[y][x];
		}
	}

	file.close();

	for (int y = 0; y < 20; ++y) {
		for (int x = 0; x < 20; ++x) {
			cout << setw(2) << setfill(' ') << arr[y][x] << ' ';
		}
		cout << endl;
	}

	int result = 0;
	for (int y = 0; y < 20; ++y) {
		for (int x = 0; x < 20; ++x) {
			if (x + 3 < 20) {
				result = max(result, arr[y][x] * arr[y][x+1] * arr[y][x+2] * arr[y][x+3]);
			}
			if (y + 3 < 20) {
				result = max(result, arr[y][x] * arr[y + 1][x] * arr[y + 2][x] * arr[y + 3][x]);
			}
			if (y + 3 < 20 && x + 3 < 20) {
				result = max(result, arr[y][x] * arr[y+1][x+1] * arr[y+2][x+2] * arr[y+3][x+3]);
			}
			if (y + 3 < 20 && x + 3 < 20) {
				result = max(result, arr[y+3][x] * arr[y+2][x+1] * arr[y+1][x+2] * arr[y][x+3]);
			}
		}
	}

	cout << "max value : " << result << endl;

	return 0;
}