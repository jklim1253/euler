#include <iostream>
#include <sstream>
#include <set>
using namespace std;
#include "inc/basic_question.hpp"
#include "inc/error_code.h"

class SOLUTION_API q003 : public basic_question
{
public :
    int execute() override final
    {
        unsigned long long input = 600851475143;

        cout << "factor of " << input << " are : " << endl;
        cout << factor<decltype(input)>(input) << endl;

        return ec::no_error;
    }
private :
    template<typename T>
    class factor
    {
        T limit;
        set<T> elements;
        void find_elements()
        {
            T N = limit;
            T element = 1;

            while (N != (element = is_prime(N)))
            {
                N = N / element;
                elements.insert(element);
            }
            elements.insert(element);
        }
    public :
        factor(const T& v)
            : limit(v)
        {
            find_elements();
        }
        friend ostream& operator << (ostream& os, const factor& ft)
        {
            for (T e : ft.elements)
            {
                os << e << " ";
            }
            return os;
        }
    private :
        template<typename T>
        T is_prime(const T& N)
        {
            T sqv = static_cast<T>(sqrt(N));
            for (T i = 2; i <= sqv; ++i)
            {
                if (N % i == 0)
                    return i;
            }

            return N;
        }

    };

};

extern "C"
{
    SOLUTION_API basic_question* CreateInstance()
    {
        std::cout << "create q003 instance" << std::endl;
        return new q003();
    }
} // extern "C"
