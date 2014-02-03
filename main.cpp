
#include<iostream>

#include "MiningMail.h"


#include "Mail.h"

#include "MailStorageTest.h"

#include "test_mail.h"

#include "Logger.h"
#include "UserMailDataset.h"
#include "ConfigManager.h"


int main(int argc, char** argv) {
    
    
    mm::ConfigManager::initConfigManager("/home/wesley/projects/MiningMail/config.json");

    mm::Logger::initLogger();

    LOG_MESSAGE("main", "Init basic parse test: ");

    bool test_Mail_res = test_mining_mail::test_Mail::test();

    std::stringstream sstr("");
    sstr << "Mail_tests == " << test_Mail_res << std::endl;
    
    mm::UserMailDataset dataset;
    dataset.loadFromLocalPath(
            std::string(mm::ConfigManager::getProperty("emailDataRootDir")));

    LOG_MESSAGE("main", sstr.str().c_str());

    mm::Logger::finalizeLogger();
    return 0;
}

