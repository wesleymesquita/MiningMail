/* 
 * File:   EnronMail.h
 * Author: Wesley Mesquita
 * Email: wesleymesquita@gmail.com     
 * Created on December 26, 2013, 9:15 PM
 */

#ifndef ENRONMAIL_H
#define	ENRONMAIL_H

#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<iterator>

#include <exception>

class Mail
{
public:
   Mail(const std::string& fileLoc);     
   const std::string& getRawMailData() const;
private:
    std::string mailData; 
};

#endif	/* ENRONMAIL_H */

