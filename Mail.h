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

#include<boost/date_time/gregorian/gregorian.hpp>

#include <exception>

class Mail {
public:
    Mail(const std::string& fileLoc);
    const std::string& getFrom() const;
    const std::vector<std::string>& getTo() const;
    const boost::gregorian::date& getDate() const;
    const std::string& getSubject() const;
    const std::string& getMailData() const;

private:

    std::string from;
    std::vector<std::string> to;
    boost::gregorian::date date;
    std::string subject;
    std::string rawData;


    std::string xFrom;
    std::vector<std::string> xTo;
    std::vector<std::string> xCC;
    std::vector<std::string> xBCC;
    std::string xFolder;
    std::string xOrigin;
    std::string xFileName;

    void loadMailRawdata(const std::string& fileLoc);
    void parseMailData();
};

#endif	/* ENRONMAIL_H */

