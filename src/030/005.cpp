#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;
#include "inc/basic_question.hpp"
#include "inc/error_code.h"

class SOLUTION_API q005 : public basic_question
{
    typedef map<int, int> depot_type;
public :
    int execute() override final
    {
        int from = 1, to = 20;

        depot_type collection;
        for (int i = from; i <= to; ++i)
        {
            depot_type factors = find_factor(i);
            for (auto it = factors.begin(); it != factors.end(); ++it)
            {
                collection[it->first] = max(collection[it->first], factors[it->first]);
            }
        }

        int result = 1;
        for (auto it = collection.begin(); it != collection.end(); ++it)
        {
            result = result*pow(it->first, it->second);
        }

        cout << "result : " << result << endl;

        return ec::no_error;
    }
private :
    depot_type find_factor(const int& n) {
        depot_type factors;
        int N = n;
        int i = 2;
        while (N != 1) {
            if (N%i == 0) {
                ++factors[i];
                N = N / i;
                i = 2;
            }
            else if (i > sqrt(N)) {
                ++factors[N];
                break;
            }
            else {
                ++i;
            }
        }
        return factors;
    }
};

extern "C"
{
    SOLUTION_API basic_question* CreateInstance()
    {
        std::cout << "create q005 instance" << std::endl;
        return new q005();
    }
} // extern "C"
