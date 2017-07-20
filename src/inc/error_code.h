#pragma once

namespace ec
{
    enum errorcode
    {
        no_error = 0,
        not_implemented_yet,
        exception_occur,

        file_not_found,
        failed_to_load_library_dynamically,
        failed_to_get_createinstance_address,

        end_of_error
    };

    static const char* error_message[] = {
        "no_error",
        "not_implemented_yet",
        "exception_occur",

        "file_not_found",
        "failed_to_load_library_dynamically",
        "failed_to_get_createinstance_address",
    };
}

