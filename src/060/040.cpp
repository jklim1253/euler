#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "../inc/basic_question.hpp"

class q040 : public basic_question<q040>
{
public :
    void execute() override final
    {
        vector<int> v{ 1,10,100,1000,10000,100000,1000000 };

        int result = 1;
        for (auto e : v)
        {
            result *= d(e);
            cout << "d(" << e << ") = " << d(e) << endl;
        }

        cout << "result : " << result << endl;
    }
private :
    inline int countof(int n)
    {
        int ret = 0;
        while (n>0)
        {
            ++ret;
            n /= 10;
        }

        return ret;
    }

    inline int indexof(int n, int index)
    {
        for (int i = 0; i < index; i++)
        {
            n /= 10;
        }

        return n % 10;
    }

    // Input
    //      n : placement index of fraction part.
    // Output
    //      ret : placement number.
    int d(int n)
    {
        int index = 0;
        while (n > countof(index))
        {
            n -= countof(index);
            index++;
        }

        return indexof(index, countof(index) - n);
    }

};

