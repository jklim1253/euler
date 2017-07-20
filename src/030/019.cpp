#include <iostream>
#include <iomanip>
using namespace std;

class Date {
private :
	int _year;
	int _month;
	int _day;
	int _week;
	static const int max_month = 12;
	static const int max_week = 7;
	static const char* const strWeek[];
public :
	Date(const int& y, const int& m, const int& d, const int& w)
		: _year(y), _month(m-1), _day(d-1), _week(w-1)
	{}

	void add_day(const int& dd) {

		_day += dd;

		_week = (_week + dd) % max_week;

		if (_day >= max_day(_year, _month)) {
			_day -= max_day(_year, _month);

			add_month();
			add_day(0);
		}
	}
	void add_month() {
		++_month;
		if (_month >= max_month) {
			_month = 0;
			add_year();
		}
	}
	void add_year() {
		++_year;
	}
	const char* get_strWeek() const {
		return strWeek[_week];
	}
	int get_year() const {
		return _year;
	}
	int get_month() const {
		return _month + 1;
	}
	int get_day() const {
		return _day + 1;
	}
	int get_week() const {
		return _week;
	}
	friend ostream& operator << (ostream& os, const Date& date) {

		os << setw(4) << setfill('0') << date._year << "-";
		os << setw(2) << setfill('0') << (date._month + 1) << "-";
		os << setw(2) << setfill('0') << (date._day + 1) << " ";
		os << date.get_strWeek();

		return os;
	}
	friend bool operator > (const Date& lhs, const Date& rhs) {
		if (lhs._year > rhs._year)
			return true;
		else if (lhs._year < rhs._year)
			return false;
		else {
			if (lhs._month > rhs._month)
				return true;
			else if (lhs._month < rhs._month)
				return false;
			else {
				if (lhs._day > rhs._day)
					return true;
				else
					return false;
			}
		}
	}
	friend bool operator == (const Date& lhs, const Date& rhs) {
		return (lhs._year == rhs._year && lhs._month == rhs._month && lhs._day == rhs._day);
	}
	friend bool operator < (const Date& lhs, const Date& rhs) {
		if (lhs._year < rhs._year)
			return true;
		else if (lhs._year > rhs._year)
			return false;
		else {
			if (lhs._month < rhs._month)
				return true;
			else if (lhs._month > rhs._month)
				return false;
			else {
				if (lhs._day < rhs._day)
					return true;
				else
					return false;
			}
		}
	}
	friend bool operator >= (const Date& lhs, const Date& rhs) {
		return (lhs > rhs || lhs == rhs);
	}
	friend bool operator <= (const Date& lhs, const Date& rhs) {
		return (lhs < rhs || lhs == rhs);
	}
private :
	inline int max_day(int y, int m) const {
		if (m == 1)
			return lean_max_day(y);

		return normal_max_day(m);
	}
	inline int normal_max_day(int m) const {
		const int max_day[] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return max_day[m];
	}
	inline int lean_max_day(int y) const {
		return (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0)) ? 29 : 28;
	}
};
const char* const Date::strWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int main(int argc, char* argv[]) {

	Date start(1900, 1, 1, 2);
	Date check(1901, 1, 1, 1);
	Date end(2001, 1, 1, 1);

	// set start date to Sunday.
	start.add_day(6);

	int result = 0;
	bool checked = false;
	while (start < end) {
		if (!checked) {
			if (check <= start)
				checked = true;
		}

		if (checked) {
			if (start.get_day() == 1)
				++result;
		}

		start.add_day(7);
	}

	cout << result << endl;


	return 0;
}