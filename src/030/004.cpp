#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
#include "inc/basic_question.hpp"
#include "inc/error_code.h"

class SOLUTION_API q004 : public basic_question
{
public :
    int execute() override final
    {
        const int from = 100;
        const int to = 999;

        cout << from << " ~ " << to << endl;

        int result = 0;
        for (int i = from; i < to; ++i)
        {
            for (int j = from; j < to; ++j)
            {
                if (palindrome(i*j))
                    result = max(result, i*j);
            }
        }
        cout << "max palindrome : " << result << endl;

        return ec::no_error;
    }
private :
    template<typename T>
    bool palindrome(const T& n) {
        T reverse = 0;
        T N = n;
        while (N > 0) {
            reverse = reverse * 10 + (N % 10);
            N = N / 10;
        }
        return (reverse == n);
    }

};

extern "C"
{
    SOLUTION_API basic_question* CreateInstance()
    {
        std::cout << "create q004 instance" << std::endl;
        return new q004();
    }
} // extern "C"
