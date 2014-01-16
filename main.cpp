
#include<iostream>

#include "Mail.h"
#include "MailStorageTest.h"

#include "test_mail.h"

int main(int argc, char** argv) {
    
    bool test_Mail_res = test_mining_mail::test_Mail::test();
    std::cout << "Mail_tests == " << test_Mail_res << std::endl; 
    return 0;
}

