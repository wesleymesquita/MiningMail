/* 
 * File:   test_Mail.cpp
 * Author: Wesley Mesquita
 * 
 * Email: wesleymesquita@gmail.com
 * 
 * Created on Dec 26, 2013, 9:59:32 PM
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <algorithm>
#include "Mail.h"

/*
 * Simple C++ Test Suite
 */

const char* original_mail =
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

bool test_getMailData() {
    Mail mail("1");
    if (mail.getMailData() != original_mail) {
        std::cerr << "Failure test_getRawMailData";
        return false;
    }
    return true;
}

bool test_getFrom() {
    Mail mail("1");
    if(mail.getFrom().compare("heather.dunton@enron.com") != 0){
        std::cerr << "Failure test_getFrom";
        return false;
    }        
    return true;
}

bool test_getTo() {
    Mail mail("1");
    if(mail.getTo().size() <= 0){        
        std::cerr << "Failure test_getTo";
        return false;     
    } 
    else{
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
    Mail mail("1");
    return false;
}

bool test_getSubject() {
    Mail mail("1");
    return false;
}

bool test_getMessageID() {
    Mail mail("1");
    //"<16159836.1075855377439.JavaMail.evans@thyme>"
    return false;
}

int main(int argc, char** argv) {

    test_getMailData();
    test_getFrom();
    test_getTo();
    test_getDate();
    test_getSubject();
    test_getMessageID();
    return (EXIT_SUCCESS);
}

