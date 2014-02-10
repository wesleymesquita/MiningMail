
#include<iostream>

#include "MiningMail.h"


#include "Mail.h"

#include "MailStorageTest.h"

#include "Logger.h"
#include "UserMailDataset.h"
#include "ConfigManager.h"

#include "test_mail.h"

int main(int argc, char** argv) {
    
    
    mm::ConfigManager::initConfigManager("/home/wesley/projects/MiningMail/config.json");

    mm::Logger::initLogger();

    LOG_MESSAGE("main", "Init basic parse test: ");

    mm::test_Mail testMail;    
    testMail.execTest();
    std::cout << testMail.getDetailResult();
    
    std::stringstream sstr("");
    
    mm::UserMailDataset dataset;
    dataset.loadFromLocalPath(
            std::string(mm::ConfigManager::getProperty("emailDataRootDir")));

    LOG_MESSAGE("main", sstr.str().c_str());

    mm::Logger::finalizeLogger();
    return 0;
}

