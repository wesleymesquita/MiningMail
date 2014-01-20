#include "Mail.h"
#include "Logger.h"

Mail::Mail(const std::string& fileLoc) {
    loadMailRawdata(fileLoc);
    parseMailData();
}

Mail::~Mail(){
    
}

// getters and setters

const std::string& Mail::getFrom() const {
    return this->from;
}

void Mail::setFrom(const std::string& _from){    
    this->from = _from;
}

const std::vector<std::string>& Mail::getTo() const {
    return this->to;
}

void Mail::setTo(const std::string& to_str){
   //this->to = to_str; 
}
    
const bpt::ptime& Mail::getDate() const {
    return this->date;
}

void Mail::setDate(const std::string& date_str) {
    std::unordered_map<std::string, std::string> date_parsed_data;

    date_parsed_data["week_day"] = date_str.substr(0, 3);
    date_parsed_data["month_day"] = date_str.substr(5, 1);
    date_parsed_data["month"] = date_str.substr(7, 3);
    date_parsed_data["year"] = date_str.substr(10, 5);
    date_parsed_data["hour"] = date_str.substr(16, 2);
    date_parsed_data["minute"] = date_str.substr(19, 2);
    date_parsed_data["second"] = date_str.substr(22, 2);
    date_parsed_data["time_zone"] = date_str.substr(24, 6);
    
    std::stringstream sstr;
    sstr << date_parsed_data["year"] << "-" 
            << date_parsed_data["month"] << "-"
            << date_parsed_data["day"] << " "
            << date_parsed_data["hour"] << ":"
            << date_parsed_data["minute"] << ":"
            << date_parsed_data["second"];

    date = bpt::ptime(bpt::time_from_string(sstr.str()));
}
    

const std::string& Mail::getSubject() const {
    return this->subject;
}

void Mail::setSubject(const std::string& subject_str){
    this->subject = subject_str;
}

    
const std::string& Mail::getMailData() const {
    return this->rawData;
}

void Mail::setMailData(const std::string& mailData_str){
    this->rawData = mailData_str;
}

const std::string& Mail::getMessageID() const {
    return this->messageID;
}

void Mail::setMessageID(const std::string& messageID_str){
    this->messageID = messageID_str;
}

void Mail::loadMailRawdata(const std::string& fileLoc) {
    
    std::ifstream mailFile;
    mailFile.open(fileLoc, std::ifstream::in);
    if (!mailFile.is_open() ) {
        std::stringstream sstr;
        sstr << "Error to open file " << fileLoc << std::endl; 
        Logger::log("Mail", sstr.str().c_str());
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
                Logger::log("Mail", sstr.str().c_str());
                throw std::exception();
            } else {
                // '+2' to jump a colon and a space after fields name
                size_t pos_end_field_value = rawData.find("\n", pos_field + field.size() + 2);
                    
                emailFields[field](std::string(
                        rawData.begin() + pos_field + field.size() + 2,
                        rawData.begin() + pos_end_field_value));
            }
        }
    } else {
        throw std::exception();
    }
}