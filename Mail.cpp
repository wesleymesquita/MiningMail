#include "Mail.h"

Mail::Mail(const std::string& fileLoc) {
    loadMailRawdata(fileLoc);
    parseMailData();
}

const std::string& Mail::getFrom() const {
    return this->from;
}

const std::vector<std::string>& Mail::getTo() const {
    return this->to;
}

const boost::gregorian::date& Mail::getDate() const {
    return this->date;
}

const std::string& Mail::getSubject() const {
    return this->subject;
}

const std::string& Mail::getMailData() const {
    return this->rawData;
}

const std::string& Mail::getMessageID() const {
    return this->messageID;
}

void Mail::loadMailRawdata(const std::string& fileLoc) {
    std::ofstream mailFile(fileLoc, std::ios::in);

    if (!mailFile.is_open()) {
        throw std::exception();
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
                    std::cout << field_keys[0] << "==" << str << std::endl;
                }},
            {field_keys[1], [&](const std::string & str) {
                    std::cout << field_keys[1] << "==" << str << std::endl;
                }},
            {field_keys[2], [&](const std::string & str) {
                    std::cout << field_keys[2] << "==" << str << std::endl;
                }},
            {field_keys[3], [&](const std::string & str) {
                    std::cout << field_keys[3] << "==" << str << std::endl;
                }},
            {field_keys[4], [&](const std::string & str) {
                    std::cout << field_keys[4] << "==" << str << std::endl;
                }}
        };

        size_t pos_field = std::string::npos;
        for (const std::string& field : field_keys) {

            pos_field = rawData.find(field);
            if (pos_field != std::string::npos) {
                throw std::exception();
            } else {
                size_t pos_end_field_value = rawData.find("\n", pos_field + field.size() + 1);
                    
                emailFields[field](std::string(
                        rawData.begin() + pos_field + field.size() + 1,
                        rawData.begin() + pos_end_field_value));
            }
        }
    } else {
        throw std::exception();
    }
}