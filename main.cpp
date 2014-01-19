
#include<iostream>

#include "Mail.h"
#include "MailStorageTest.h"

#include "test_mail.h"

#include "Logger.h"

int main(int argc, char** argv) {
    
    
    Logger::initLogger(R"(c:\tmp\log.tmp)");
    Logger::log("Init basic parse test: ");
    bool test_Mail_res = test_mining_mail::test_Mail::test();
    std::cout << "Mail_tests == " << test_Mail_res << std::endl; 
    Logger::finalizeLogger();
    return 0;
}

