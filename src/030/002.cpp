#include <iostream>
#include <sstream>
using namespace std;
#include "inc/basic_question.hpp"
#include "inc/error_code.h"

/*
 * find the sum of even-valued terms in the Fibonacci sequence.
 *
 */
class SOLUTION_API q002 : public basic_question
{
public :
    int execute() override final
    {
        int limit = 4000000;

        int sum = sum_of_fibo_range(1, limit, [](const int& v) -> bool {
            return (v % 2 == 0);
        });
        cout << "sum of those : " << sum << endl;

        return ec::no_error;
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

extern "C"
{
    SOLUTION_API basic_question* CreateInstance()
    {
        std::cout << "create q002 instance" << std::endl;
        return new q002();
    }
} // extern "C"
