#include <iostream>
using namespace std;

uint32_t sum_of_divisor(const uint32_t& n) {
	uint32_t sum = 1;
	for (uint32_t i = 2; i <= n / i; ++i) {
		if (n%i == 0) {
			if (i == n / i)
				sum += i;
			else
				sum += i + n / i;
		}
	}

	return sum;
}
template<typename T>
T sum_of_range(const T& from, const T& to) {
	return (from + to)*(to - from + 1) / 2;
}
template<uint32_t total_bits, uint8_t bits_per_word>
struct word_size {
	static const uint32_t value = (total_bits / bits_per_word) + ((total_bits % bits_per_word == 0) ? 0 : 1);
};
template<typename T, uint32_t N, uint8_t BPW = sizeof(T)*8>
inline void set_word_by_index(T(&word)[N], const uint32_t& index) {
	word[index / BPW] = word[index / BPW] | (0x01 << (index%BPW));
}
template<typename T, uint32_t N, uint8_t BPW = sizeof(T)*8>
inline bool get_word_by_index(T(&word)[N], const uint32_t& index) {
	return (word[index / BPW] & (0x01 << (index%BPW))) == (0x01 << (index%BPW));
}
int solution() {
	static const uint32_t limit = 28123+1;
	static const uint8_t bits_per_word = 32;

	uint32_t is_abundants[word_size<limit, bits_per_word>::value] = { 0, };
	uint32_t combination[word_size<limit, bits_per_word>::value] = { 0, };
	uint32_t count_of_abundants = 0;
	uint32_t abundants[limit] = { 0, };

	uint32_t sum_of_combination = 0;
	for (uint32_t i = 1; i < limit; ++i) {
		uint32_t sod = sum_of_divisor(i);
		if (sod <= i) continue;

		set_word_by_index(is_abundants, i);
		abundants[count_of_abundants] = i;
		++count_of_abundants;

		for (uint32_t j = 0; j < count_of_abundants; ++j) {
			if (i + abundants[j] >= limit) break;

			if (!get_word_by_index(combination, i + abundants[j])) {
				sum_of_combination += i + abundants[j];
				set_word_by_index(combination, i + abundants[j]);
			}
		}
	}

	cout << "solution : " << (sum_of_range(1, 28123) - sum_of_combination) << endl;

	return 0;
}

int main(int argc, char* argv[]) {

	solution();

	return 0;
}