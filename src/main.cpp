#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <memory>
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
        cout << "\nelapsed time : " << fixed << (chrono::duration<double>(chrono::steady_clock::now() - st)).count() << endl;
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

int printfile(const string& filepath)
{
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
        cout << setw(4) << right << (++line_number) << ' ' << line << '\n';
    }

    file.close();

    return ec::no_error;
}

int print_source_file(int selection);
int execute_shared_function(int selection);

int main()
{
    // select question number.
    //
    // load question solution file and view on console.
    //
    bool manual_stop = false;
    const string error_msg = "error code : ";

    while (!manual_stop)
    {
        string line;
        int select = 0;
        do {
            std::cout << "================================================================================\n";
            std::cout << "select number of question to view( > 0, enter quit to exit) :> ";
            getline(std::cin, line);
            select = atoi(line.c_str());
        } while (!(select >= 0));

        if (select == 0 && line == "quit")
        {
            manual_stop = true;
            continue;
        }

        int error;
        // view source of selected solution.
        if ((error = print_source_file(select)) != ec::no_error)
        {
            cout << error_msg << error << " : " << ec::error_message[error] << endl;
        }

        // execute selected solution.
        if ((error = execute_shared_function(select)) != ec::no_error)
        {
            cout << error_msg << error << " : " << ec::error_message[error] << endl;
        }
    } // while (!manual_stop)

    return ec::no_error;
}

int print_source_file(int selection)
{
    const int group_size = 30;

    const int folder = group_size * (1 + (selection-1)/group_size);

    std::stringstream source_path;
    source_path << euler_solution::base_dir << "/src/";
    source_path << setw(3) << setfill('0') << folder << "/";
    source_path << setw(3) << setfill('0') << selection << ".cpp";

    return do_work(printfile, source_path.str());
}

class SharedLoader
{
    HMODULE module;
public :
    SharedLoader(const string& name)
    {
        module = ::LoadLibrary(name.c_str());
        if (module == NULL) throw ec::failed_to_load_library_dynamically;
    }
    ~SharedLoader()
    {
        ::FreeLibrary(module);
    }
    operator HMODULE() const
    {
        return module;
    }
};

template<typename Function>
class SharedExecutor
{
    Function operation;
    SharedLoader& library;
public :
    SharedExecutor(SharedLoader& _library, const string& _name)
        : library(_library)
        , operation(Function(::GetProcAddress(_library, _name.c_str())))
    {
        if (operation == NULL) throw ec::failed_to_get_createinstance_address;
    }
    ~SharedExecutor()
    {
    }
    int operator()()
    {
        unique_ptr<basic_question> quest((*operation)());

        return do_work(&basic_question::execute, quest.get());
    }
};

int execute_shared_function(int selection)
{
    std::stringstream dllname;
    dllname << setw(3) << setfill('0') << selection << ".dll";

    try
    {
        SharedLoader shared_library(dllname.str());

        SharedExecutor<decltype(&CreateInstance)> shared_execution(shared_library, "CreateInstance");

        return shared_execution();
    }
    catch (ec::errorcode error)
    {
        return error;
    }
    catch (...)
    {
        return ec::exception_occur;
    }

    return ec::no_error;
}
