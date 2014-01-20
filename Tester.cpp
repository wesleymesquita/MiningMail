
void Tester::assertStrings(
        const char* function_name,
        const char* expected,
        const char* result) {
    
    
    
    if (std::string(expected).compare(result) != 0) {
        const char* FAILED = "FAILED";
        Logger::log(className.c_str(), "[FAILED] getSubject failed");
        return false;
    } else {
        Logger::log(className.c_str(), "");
        return true;
    }
}