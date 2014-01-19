/* 
 * File:   test_Mail.h
 * Author: wesley
 *
 * Created on 15 de Janeiro de 2014, 20:48
 */

#ifndef TEST_MAIL_H
#define	TEST_MAIL_H

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include "Mail.h"
#include "Logger.h"

namespace test_mining_mail {

    const char* original_data_test_Mail =
            R"(Message-ID: <16159836.1075855377439.JavaMail.evans@thyme>
Date: Fri, 7 Dec 2001 10:06:42 -0800 (PST)
From: heather.dunton@enron.com
To: k..allen@enron.com
Subject: RE: West Position
Mime-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Transfer-Encoding: 7bit
X-From: Dunton, Heather </O=ENRON/OU=NA/CN=RECIPIENTS/CN=HDUNTON>
X-To: Allen, Phillip K. </O=ENRON/OU=NA/CN=RECIPIENTS/CN=Pallen>
X-cc: 
X-bcc: 
X-Folder: \Phillip_Allen_Jan2002_1\Allen, Phillip K.\Inbox
X-Origin: Allen-P
X-FileName: pallen (Non-Privileged).pst

 
Please let me know if you still need Curve Shift.

Thanks,
Heather
 -----Original Message-----
From: 	Allen, Phillip K.  
Sent:	Friday, December 07, 2001 5:14 AM
To:	Dunton, Heather
Subject:	RE: West Position

Heather,

Did you attach the file to this email?

 -----Original Message-----
From: 	Dunton, Heather  
Sent:	Wednesday, December 05, 2001 1:43 PM
To:	Allen, Phillip K.; Belden, Tim
Subject:	FW: West Position

Attached is the Delta position for 1/16, 1/30, 6/19, 7/13, 9/21


 -----Original Message-----
From: 	Allen, Phillip K.  
Sent:	Wednesday, December 05, 2001 6:41 AM
To:	Dunton, Heather
Subject:	RE: West Position

Heather,

This is exactly what we need.  Would it possible to add the prior day for each of the dates below to the pivot table.  In order to validate the curve shift on the dates below we also need the prior days ending positions.

Thank you,

Phillip Allen

 -----Original Message-----
From: 	Dunton, Heather  
Sent:	Tuesday, December 04, 2001 3:12 PM
To:	Belden, Tim; Allen, Phillip K.
Cc:	Driscoll, Michael M.
Subject:	West Position


Attached is the Delta position for 1/18, 1/31, 6/20, 7/16, 9/24



 << File: west_delta_pos.xls >> 

Let me know if you have any questions.


Heather)";

const char* original_data_test_Mail_file = R"(C:\Users\wesley\Downloads\enron_mail_20110402\maildir\allen-p\inbox\1)";    
    
    class test_Mail {
    private:

      bool test_getMailData() {
            Mail mail(original_data_test_Mail_file);
            if (mail.getMailData() != original_data_test_Mail) {
                std::cerr << "Failure test_getRawMailData";
                return false;
            }
            return true;
        }

        bool test_getFrom() {
            Mail mail(original_data_test_Mail_file);
            if (mail.getFrom().compare("heather.dunton@enron.com") != 0) {
                std::cerr << "Failure test_getFrom";
                return false;
            }
            return true;
        }

        bool test_getTo() {
            Mail mail(original_data_test_Mail_file);
            if (mail.getTo().size() <= 0) {
                std::cerr << "Failure test_getTo";
                return false;
            } else {
                std::vector<std::string> expected = {"k..allen@enron.com"};
                bool equal = std::equal(mail.getTo().begin(),
                        mail.getTo().end(),
                        expected.begin());
                std::cerr << "Failure test_getTo";
                return equal;
            }
            return true;
        }

        bool test_getDate() {
            Mail mail(original_data_test_Mail_file);
            return false;
        }

        bool test_getSubject() {
            Mail mail(original_data_test_Mail_file);
            return false;
        }

        bool test_getMessageID() {
            Mail mail(original_data_test_Mail_file);
            const std::string expected_message_id = 
                "<16159836.1075855377439.JavaMail.evans@thyme>";
            if( mail.getMessageID().compare(expected_message_id) != 0 ){
              Logger::log("Error Mail::getMessageID failed ");  
              return false;
            }
            return true;
        }
    public:

        static int test() {
            test_Mail tester;
            
            std::vector< std::function<bool()> > test_functions  = 
            { { [&]()->bool{return tester.test_getMessageID();} },
              { [&]()->bool{return false; /*tester.test_getMessageID();*/} },
              { [&]()->bool{return false; /*tester.test_getFrom();*/} }, 
              { [&]()->bool{return false; /*tester.test_getTo();*/} },
              { [&]()->bool{return false; /*tester.test_getDate();*/} },
              { [&]()->bool{return false; /*tester.test_getSubject();*/} },
              { [&]()->bool{return false; /*tester.test_getMessageID();*/} }         
            };           
        
            std::vector<bool> result; 
            result.reserve(test_functions.size());
            
            std::vector<bool> expected_result(test_functions.size(), true); 
            
            for(auto f : test_functions){
                result.push_back(f());
            }
          
            return std::equal(result.begin(),result.end(), expected_result.begin());
        }
    };
}

#endif	/* TEST_MAIL_H */

