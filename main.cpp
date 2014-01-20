
#include<iostream>

#include "Mail.h"
#include "MailStorageTest.h"

#include "test_mail.h"

#include "Logger.h"

int main(int argc, char** argv) {
    
    
    Logger::initLogger("Mail", R"(c:\tmp\mail.log)");
    Logger::log("Mail", "Init basic parse test: ");
    bool test_Mail_res = test_mining_mail::test_Mail::test();
    std::stringstream sstr; 
    sstr << "Mail_tests == " << test_Mail_res << std::endl; 
    Logger::log("Mail", sstr.str().c_str());
    Logger::finalizeLogger("Mail");
    return 0;
}

