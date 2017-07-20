#include <iostream>
#include <sstream>
using namespace std;
#include "../inc/basic_question.hpp"

/*
 * find the sum of even-valued terms in the Fibonacci sequence.
 *
 */
class q002 : public basic_question<q002>
{
public :
    void execute() override final
    {
        int limit = 1000;

        int sum = sum_of_fibo_range(1, limit, [](const int& v) -> bool {
            return (v % 2 == 0);
        });
        cout << "sum of those : " << sum << endl;

    }
private :
    template<typename T, typename UnaryFunction>
    T sum_of_fibo_range(const T& from, const T& to, UnaryFunction condi)
    {
        const int size = 3;
        T sum = 0;
        T arr[size] = { 1,2, };
        int index = 0;
        while (arr[index%size] <= to)
        {
            arr[(index + 2)%size] = arr[(index + 1)%size] + arr[index%size];

            if (arr[index%size] >= from && condi(arr[index%size]))
            {
                sum += arr[index%size];
            }

            ++index;
        }

        return sum;
    }
};

