/* 
 * File:   MailStorageTest.cpp
 * Author: wesley
 * 
 * Created on 1 de Janeiro de 2014, 21:24
 */

#include "MailStorageTest.h"
namespace mm {

    MailStorageTest::MailStorageTest() {
    }

    MailStorageTest::~MailStorageTest() {
    }

    bool MailStorageTest::test() {
        MailStorage storage("C:\\Users\\wesley\\Downloads\\enron_mail_20110402\\maildir");
        storage.loadUsers();
    }
};
