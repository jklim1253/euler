#pragma once

class basic_question
{
public :
    virtual int execute() = 0;
};

#ifdef SOLUTION_EXPORTS
#define SOLUTION_API __declspec(dllexport)
#else
#define SOLUTION_API __declspec(dllimport)
#endif

extern "C" {
SOLUTION_API basic_question* CreateInstance();
}
