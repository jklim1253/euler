#include <iostream>
#include <string>
using namespace std;

string hundred(const int& n) {
	const char* msg[] = {
		"",
		"onehundred",
		"twohundred",
		"threehundred",
		"fourhundred",
		"fivehundred",
		"sixhundred",
		"sevenhundred",
		"eighthundred",
		"ninehundred",
		"onethousand",
	};

	return msg[n];
}
string and(bool b) {
	return (b) ? "and" : "";
}
string tens(const int& n) {
	const char* msg[] = {
		"",
		"",
		"twenty",
		"thirty",
		"forty",
		"fifty",
		"sixty",
		"seventy",
		"eighty",
		"ninety"
	};
	return msg[n];
}
string one(const int& n) {
	const char* msg[] = {
		"",
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};
	return msg[n];
}
string ten(const int& n) {
	if (n >= 20) {
		return tens(n / 10) + one(n % 10);
	}
	else if (n <= 19 && n >= 10) {
		const char* msg[] = {
			"ten",
			"eleven",
			"twelve",
			"thirteen",
			"fourteen",
			"fifteen",
			"sixteen",
			"seventeen",
			"eighteen",
			"nineteen"
		};
		return msg[n % 10];
	}
	
	return one(n);
}
string english(const int& n) {
	return hundred(n / 100)
	+ and ((n/100 != 0) && (n%100 != 0))
	+ ten(n % 100);
}

int main(int argc, char* argv[]) {

	int result = 0;
	for (int i = 1; i <= 1000; ++i) {
		result += english(i).length();
	}

	cout << result << endl;

	return 0;
}