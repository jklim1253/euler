#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <functional>
using namespace std;
#include "inc/error_code.h"
#include "inc/basic_question.hpp"
#include "inc/define.h"

#include <windows.h>

class elapsed_time_checker
{
    chrono::steady_clock::time_point st;
public :
    elapsed_time_checker() : st(chrono::steady_clock::now()) {}
    ~elapsed_time_checker()
    {
        cout << "\nelapsed time : " << (chrono::duration<double>(chrono::steady_clock::now() - st)).count() << endl;
    }
};

template<typename Function, typename...Arguments>
int do_work(Function&& func, Arguments&& ... args)
{
    elapsed_time_checker etc;
    return func(args...);
}
template<typename MemberFunction, typename Cls, typename...Arguments>
int do_work(MemberFunction&& func, Cls* obj, Arguments&&...args)
{
    elapsed_time_checker etc;
    return (obj->*func)(args...);
}

template<typename T>
int printfile(const T& _filepath)
{
    const string filepath(_filepath);

    cout << "filepath : " << filepath << endl;

    fstream file;
    file.open(filepath, ios_base::in);
    if (!file.good())
    {
        return ec::file_not_found;
    }

    int line_number = 0;
    string line;
    while (getline(file, line))
    {
        cout << setw(4) << right << (++line_number) << "    ";
        cout << line << '\n';
    }

    file.close();

    return ec::no_error;
}

int main()
{
    // select question number.
    //
    // load question solution file and view on console.
    //
    const int group_size = 30;
    int select = 0;
    do {
        std::cout << "select number of question to view( > 0) : ";
        std::cin >> select;
    } while (!(select > 0));

    int folder = group_size * (1 + (select-1)/group_size);

    std::stringstream ss;
    ss << euler_solution::base_dir << "/src/";
    ss << setw(3) << setfill('0') << folder << "/";
    ss << setw(3) << setfill('0') << select;
    ss << ".cpp";

    const string srcfile(ss.str());
    int ret;
    if ((ret = do_work(printfile<decltype(srcfile)>, srcfile)) != ec::no_error)
    {
        cout << "error code : " << ret << endl;
    }

    std::stringstream dllname;
    dllname << setw(3) << setfill('0') << select << ".dll";

    HMODULE hSolution = ::LoadLibrary(dllname.str().c_str());
    if (hSolution == NULL)
    {
        cout << "failed to load library dynamically." << endl;
        return ec::failed_to_load_library_dynamically;
    }

    typedef basic_question*(*CreateInstanceFunction)();
    CreateInstanceFunction CreateInstanceAddr = (CreateInstanceFunction)::GetProcAddress(hSolution, "CreateInstance");
    if (CreateInstanceAddr == NULL)
    {
        cout << "failed to get CreateInstance address." << endl;
        return ec::failed_to_get_createinstance_address;
    }

    basic_question* quest = (*CreateInstanceAddr)();

    do_work(&basic_question::execute, quest);

    return ec::no_error;
}

