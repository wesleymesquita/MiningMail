
#include<iostream>
#include<boost/current_function.hpp>


#include "Mail.h"
#include "MailStorageTest.h"

#include "test_mail.h"

#include "Logger.h"
#include "UserMailDataset.h"

int main(int argc, char** argv) {
    
    
    Logger::initLogger("Mail", R"(c:\tmp\mail.log)");
    Logger::log(BOOST_CURRENT_FUNCTION, __LINE__,"main", "Init basic parse test: ");
    bool test_Mail_res = test_mining_mail::test_Mail::test();
    std::stringstream sstr; 
    sstr << "Mail_tests == " << test_Mail_res << std::endl; 
    UserMailDataset dataset;
    dataset.loadFromLocalPath(std::string(R"(C:\Users\wesley\Downloads\enron_mail_20110402\maildir)"));
    Logger::log(BOOST_CURRENT_FUNCTION, __LINE__, "main", sstr.str().c_str());
    Logger::finalizeLogger("main");
    return 0;
}

