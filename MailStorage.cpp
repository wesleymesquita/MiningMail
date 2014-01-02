/* 
 * File:   MailStorage.cpp
 * Author: Wesley Mesquita
 * Email: wesleymesquita@gmail.com
 * 
 */

#include "MailStorage.h"

MailStorage::MailStorage(const std::string& _rootDir) {
    if(!fs::exists(_rootDir) && fs::is_directory(_rootDir)){
        throw std::exception();
    }
    else
    {
        rootDir = _rootDir;
    }
}

void MailStorage::loadUsers()
{
    fs::directory_iterator it(rootDir);
    while(it != fs::directory_iterator()){
        std::cout << it->path() << std::endl;
        it++;
    }     
}

MailStorage::~MailStorage() {
}

