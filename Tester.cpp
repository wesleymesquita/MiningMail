#include "Tester.h"

bool Tester::assertStrings(
        const char* function_name,
        const char* expected,
        const char* result) { 
    if (std::string(expected).compare(result) != 0) {
        LOG_MESSAGE( className.c_str(), "[FAILED] getSubject failed");
        return false;
    } else {
        LOG_MESSAGE(className.c_str(), "");
        return true;
    }
}