#include "Mail.h"

Mail::Mail(const std::string& fileLoc) {
    loadMailRawdata(fileLoc);
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

}