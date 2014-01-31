/* 
 * File:   test_Mail.h
 * Author: Wesley Mesquita
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

#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/current_function.hpp>

#include<MiningMail.h>
#include "Mail.h"

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

    const char* original_data_test_Mail_file = R"(/home/wesley/projects/MiningMail/1)";

    class test_Mail {
    private:
        const Mail mail;
        
        
        
        bool test_getMailData() {
            if (mail.getMailData().compare(original_data_test_Mail) != 0) {
                LOG_MESSAGE( "test_Mail", "Error Mail::getSubject failed");
                return false;
            }
            return true;
        }

        bool test_getFrom() {
            if (mail.getFrom().compare("heather.dunton@enron.com") != 0) {
                LOG_MESSAGE( "test_Mail", "Failure test_getFrom");                
                return false;
            }
            return true;
        }

        bool test_getTo() {
            if (mail.getTo().size() <= 0) {
                std::cerr << "Failure test_getTo";
                return false;
            } else {
                std::vector<std::string> expected = {"k..allen@enron.com"};
                bool equal = std::equal(mail.getTo().begin(),
                        mail.getTo().end(),
                        expected.begin());
                
                LOG_MESSAGE( "test_Mail", "Failure test_getTo");
                return equal;
            }
        }

        bool test_getDate() {
            // Fri, 7 Dec 2001 10:06:42 -0800 (PST)
            boost::posix_time::ptime expected_date;
            const std::string date_str("2001-12-7 10:06:42");
            expected_date = boost::posix_time::time_from_string(date_str);
            if (expected_date != mail.getDate()) {
                LOG_MESSAGE( "test_Mail", "Failure test_getDate");
                return false;
            }
            return true;
        }

        bool test_getSubject() {
            const std::string expected_subject = "RE: West Position";
            if (mail.getSubject().compare(expected_subject) != 0) {
                LOG_MESSAGE( "test_Mail", "Error Mail::getSubject failed");
                return false;
            }
            return true;
        }

        bool test_getMessageID() {
            const std::string expected_message_id =
                    "<16159836.1075855377439.JavaMail.evans@thyme>";
            if (mail.getMessageID().compare(expected_message_id) != 0) {
                LOG_MESSAGE( "test_Mail", "Error Mail::getMessageID failed");
                return false;
            }
            return true;
        }
    public:
        test_Mail():
            mail(original_data_test_Mail_file){           
        }    
        
        static int test() {
            test_Mail tester;

            std::vector < std::function<bool()> > test_functions = {
                { [&]()->bool {
                        return tester.test_getMessageID();
                    }},
                { [&]()->bool {
                        return tester.test_getFrom();
                    }},
                { [&]()->bool {
                        return tester.test_getTo();
                    }},
                { [&]()->bool {
                        return tester.test_getDate();
                    }},
                { [&]()->bool {
                        return tester.test_getSubject();
                    }}
            };

            std::vector<bool> result;
            result.reserve(test_functions.size());

            std::vector<bool> expected_result(test_functions.size(), true);

            for (auto f : test_functions) {
                result.push_back(f());
            }

            return std::equal(result.begin(), result.end(), expected_result.begin());
        }
    };
}

#endif	/* TEST_MAIL_H */

