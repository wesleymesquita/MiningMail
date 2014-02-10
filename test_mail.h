/* 
 * File:   test_Mail.h
 * Author: Wesley Mesquita
 * Email: wesleymesquita@gmail.com
 * 
 * Created on 15 de Janeiro de 2014, 20:48
 */

#ifndef TEST_MAIL_H
#define	TEST_MAIL_H

#include "Tester.h"

#include "Mail.h"

namespace mm
{
    class test_Mail : public Tester {
    public:
        test_Mail();
    private:
        static const char* original_data_test_Mail;
        static const char* original_data_test_Mail_file;

        const Mail mail;

        bool test_getMailData();
        bool test_getFrom();
        bool test_getTo();
        bool test_getDate();
        bool test_getSubject();
        bool test_getMessageID();
        bool test_toJSON();
        bool test_validateMail();
    };
};
#endif	/* TEST_MAIL_H */

