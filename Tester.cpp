#include "Tester.h"

bool Tester::assertStrings(
        const char* function_name,
        const char* expected,
        const char* result) { 
    if (std::string(expected).compare(result) != 0) {
        Logger::log(BOOST_CURRENT_FUNCTION, __LINE__, className.c_str(), "[FAILED] getSubject failed");
        return false;
    } else {
        Logger::log(BOOST_CURRENT_FUNCTION, __LINE__,className.c_str(), "");
        return true;
    }
}