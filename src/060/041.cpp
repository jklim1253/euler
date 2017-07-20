#include <iostream>
#include <vector>
using namespace std;
#include "../inc/basic_question.hpp"

// pandigital prime

class q041 : public basic_question<q041>
{
public :
    void execute() override final
    {
    }
private :
    template<typename T>
    bool is_prime(const T& v)
    {
        T n = 2;
        while (n*n <= v)
        {
            if (v % n == 0)
                return false;
        }

        return true;
    }
    template<typename T>
    T pandigital(const T& digit, size_t index)
    {
        return T();
    }
};

