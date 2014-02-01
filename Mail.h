/* 
 * File:   EnronMail.h
 * Author: Wesley Mesquita
 * Email: wesleymesquita@gmail.com     
 * Created on December 26, 2013, 9:15 PM
 */

#ifndef MAIL_H
#define	MAIL_H

#include<string>

namespace mm {

    namespace bpt = boost::posix_time;

    class Mail {
    public:
        Mail(const std::string& fileLoc);
        virtual ~Mail();
        const std::string& getFrom() const;
        const std::vector<std::string>& getTo() const;
        const bpt::ptime& getDate() const;
        const std::string& getSubject() const;
        const std::string& getMailData() const;
        const std::string& getMessageID() const;

    private:
        std::string messageID;
        std::string from;
        std::vector<std::string> to;
        bpt::ptime date;
        std::string subject;
        std::string rawData;


        std::string xFrom;
        std::vector<std::string> xTo;
        std::vector<std::string> xCC;
        std::vector<std::string> xBCC;
        std::string xFolder;
        std::string xOrigin;
        std::string xFileName;

        void setFrom(const std::string& from_str);
        void setTo(const std::string& to_str);
        void setDate(const std::string& date_str);
        void setSubject(const std::string& subject_str);
        void setMailData(const std::string& mailData_str);
        void setMessageID(const std::string& messageID_str);


        void loadMailRawdata(const std::string& fileLoc);
        void parseMailData();


    };
};
#endif	/* MAIL_H */

