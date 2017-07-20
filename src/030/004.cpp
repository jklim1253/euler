#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
#include "../inc/basic_question.hpp"

class q004 : public basic_question<q004>
{
public :
    void execute() override final
    {
        int from, to;
        from = 1;
        to = 10000;

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

