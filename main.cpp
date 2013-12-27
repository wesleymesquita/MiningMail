
#include<iostream>

#include "Mail.h"

int main(int argc, char** argv) {
    
    Mail mail(R"(C:\Users\wesley\Downloads\enron_mail_20110402\maildir\allen-p\inbox\1)");
    std::cout << mail.getRawMailData();
}

