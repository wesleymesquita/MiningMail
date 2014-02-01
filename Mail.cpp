#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <exception>
#include <functional>
#include <unordered_map>

#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/date_time/gregorian/gregorian.hpp>
#include<boost/current_function.hpp>
#include <boost/regex.hpp>


#include "Mail.h"
#include "MiningMail.h"


Mail::Mail(const std::string& fileLoc) {
    loadMailRawdata(fileLoc);
    parseMailData();
}

Mail::~Mail() {

}

// getters and setters

const std::string& Mail::getFrom() const {
    return this->from;
}

void Mail::setFrom(const std::string& _from) {
    this->from = _from;
}

const std::vector<std::string>& Mail::getTo() const {
    return this->to;
}

void Mail::setTo(const std::string& to_str) {
    std::vector<std::string> res;
    size_t pos_begin = 0;
    
    size_t pos_end = to_str.find(',', pos_begin);
    if(pos_end == std::string::npos){
       res.push_back(to_str); 
    }
    else{
        while(pos_end != std::string::npos){
            std::string tmp = to_str.substr(pos_begin, pos_end);
            res.push_back(std::move(tmp));
            pos_begin = pos_end + 1;
            pos_end = to_str.find(',', pos_begin); 
        }        
    }
    
    this->to = std::move(res); 
}

const bpt::ptime& Mail::getDate() const {
    return this->date;
}

void Mail::setDate(const std::string& date_str) {
    std::unordered_map<std::string, std::string> date_parsed_data;

    static std::unordered_map<std::string, std::string> months = 
    {{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, 
    {"Apr", "04"}, {"May", "05"}, {"Jun", "06"}, 
    {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, 
    {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}};
    
    //date_str example: Sat, 20 Oct 2001 03:10:58 -0700 (PDT)    
    // Expression about was verified at http://regex101.com/r/rC1pR9
    // ([A-Z][a-z][a-z]),\s([0-9]+)\s([A-Z][a-z][a-z])\s([0-9]{4,4})\s([0-2][0-9]:[0-5][0-9]:[0-5][0-9])\s(-[0-9]{4,4})\s(\([A-Z]{3,3}\))
    
    const static std::string reg_exp = 
    "([A-Z][a-z][a-z]),\\s([0-9]+)\\s([A-Z][a-z][a-z])\\s([0-9]{4,4})\\s([0-2][0-9]):([0-5][0-9]):([0-5][0-9])\\s(-[0-9]{4,4})\\s(\\([A-Z]{3,3}\\))";
    
    boost::regex date_rgx(reg_exp);   
    boost::sregex_iterator it(date_str.begin(), date_str.end(), date_rgx);
    
    date_parsed_data["week_day"] = (*it)[0].str();
    
    date_parsed_data["month_day"] = (*it)[1].str().size() == 1 ?
            std::string("0") + (*it)[1].str() :
            (*it)[1].str();
    
    date_parsed_data["month"] = months[ (*it)[2].str() ];
     
    date_parsed_data["year"] = (*it)[3].str();
            
    date_parsed_data["hour"] = (*it)[4].str();
    date_parsed_data["minute"] = (*it)[5].str();
    date_parsed_data["second"] = (*it)[6].str();
    date_parsed_data["time_zone"] = (*it)[7].str();
    
    const std::locale format = std::locale(std::locale::classic(),
            new bpt::time_input_facet("%04Y-%02m-%02d %H:%M:%S"));


    std::stringstream sstr;
    sstr << date_parsed_data["year"] << "-"
            << date_parsed_data["month"] << "-"
            << date_parsed_data["month_day"] << " "
            << date_parsed_data["hour"] << ":"
            << date_parsed_data["minute"] << ":"
            << date_parsed_data["second"];
    sstr.imbue(format);
    
    try{
        date = bpt::ptime(bpt::time_from_string(sstr.str()));
    }catch(std::exception& e){
        std::stringstream sstr;
        sstr << "Could not convert " << date_str << " to internal date format:  "
             << "Date was parsed as : "
             << " month == " << date_parsed_data["year"]
             << " month_day == " << date_parsed_data["month_day"]
             << " hour == " << date_parsed_data["hour"]
             << " minute == " << date_parsed_data["minute"]
             << " second == " << date_parsed_data["second"]               
             << " Exception: " << e.what();
        LOG_MESSAGE("Mail", sstr.str().c_str() );
    }
  }

const std::string& Mail::getSubject() const {
    return this->subject;
}

void Mail::setSubject(const std::string& subject_str) {
    this->subject = subject_str;
}

const std::string& Mail::getMailData() const {
    return this->rawData;
}

void Mail::setMailData(const std::string& mailData_str) {
    this->rawData = mailData_str;
}

const std::string& Mail::getMessageID() const {
    return this->messageID;
}

void Mail::setMessageID(const std::string& messageID_str) {
    this->messageID = messageID_str;
}

void Mail::loadMailRawdata(const std::string& fileLoc) {

    std::ifstream mailFile;
    mailFile.open(fileLoc, std::ifstream::in);
    if (!mailFile.is_open()) {
        std::stringstream sstr;
        sstr << "Error to open file " << fileLoc << std::endl;
        Logger::log(BOOST_CURRENT_FUNCTION, __LINE__, "Mail", sstr.str().c_str());
    } else {
        if (mailFile.good()) {
            std::stringstream s;
            s << mailFile.rdbuf();
            rawData = s.str();
        }
        mailFile.close();
    }
}

void Mail::parseMailData() {
    if (rawData.size() > 0) {

        const std::vector<std::string> field_keys = {"Message-ID", "Date", "From", "To", "Subject"};

        std::unordered_map < std::string, std::function< void(const std::string)> > emailFields = {
            {field_keys[0], [&](const std::string & str) {
                    setMessageID(str);
                }},
            {field_keys[1], [&](const std::string & str) {
                    setDate(str);
                }},
            {field_keys[2], [&](const std::string & str) {
                    setFrom(str);
                }},
            {field_keys[3], [&](const std::string & str) {
                    setTo(str);
                }},
            {field_keys[4], [&](const std::string & str) {
                    setSubject(str);
                }}
        };

        size_t pos_field = std::string::npos;
        for (const std::string& field : field_keys) {

            pos_field = rawData.find(field);
            if (pos_field == std::string::npos) {
                std::stringstream sstr;
                sstr << "Could not find field " << field;
                LOG_MESSAGE("Mail", sstr.str().c_str());
            } else {
                // '+2' to jump a colon and a space after fields name
                size_t pos_end_field_value = rawData.find("\n", pos_field + field.size() + 2);

                emailFields[field](std::string(
                        rawData.begin() + pos_field + field.size() + 2,
                        rawData.begin() + pos_end_field_value));
            }
        }
    } else {
        std::stringstream sstr;
        sstr << "Error Mail::parseMailData()";
        LOG_MESSAGE("Mail", sstr.str().c_str());
    }
}