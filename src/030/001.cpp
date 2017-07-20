#include <iostream>
#include <sstream>
using namespace std;
#include "inc/basic_question.hpp"
#include "inc/error_code.h"

/*
 * find the sum of all the multiples of 3 or 5 below limit.
 */
class SOLUTION_API q001 : public basic_question
{
public :
    int execute() override final
    {
        const int limit = 1000;

        int result = sum_of_multiples(limit, 3, 5);

        cout << "result is " << result << endl;

        return ec::no_error;
    }
private :
    template<typename T>
    inline bool dividable(const T& target, const T& arg) {
        return (target%arg == 0);
    }
    template<typename T, typename First, typename... Rest>
    inline bool dividable(const T& target, const First& first, const Rest&... args) {
        return dividable(target, first) || dividable(target, args...);
    }
    template<typename T, typename... Arguments>
    T sum_of_multiples(const T& limit, const Arguments&... args) {
        T sum = 0;
        for (T i = 1; i <= limit; ++i) {
            if (dividable(i, args...)) {
                sum += i;
                cout << i << ' ';
            }
        }
        cout << endl;
        return sum;
    }
};

extern "C"
{
    SOLUTION_API basic_question* CreateInstance()
    {
        std::cout << "create q001 instance" << std::endl;
        return new q001();
    }
} // extern "C"
