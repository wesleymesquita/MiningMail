#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <exception>
#include <functional>
#include <unordered_map>
#include <memory>
#include <locale>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/current_function.hpp>
#include <boost/regex.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "Mail.h"
#include "MiningMail.h"


namespace mm {

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
        boost::split(res, to_str, boost::is_any_of(","));
        std::for_each(res.begin(), res.end(),
                [&](std::string & str) {
                    std::remove_if(str.begin(), str.end(), [](char c) {
                        return std::isspace(c); });
                });
        this->to = std::move(res);
    }

    const bpt::ptime& Mail::getDate() const {
        return this->date;
    }

    void Mail::setDate(const std::string& date_str) {
        std::unordered_map<std::string, std::string> date_parsed_data;

        static std::unordered_map<std::string, std::string> months = {
            {"Jan", "01"},
            {"Feb", "02"},
            {"Mar", "03"},
            {"Apr", "04"},
            {"May", "05"},
            {"Jun", "06"},
            {"Jul", "07"},
            {"Aug", "08"},
            {"Sep", "09"},
            {"Oct", "10"},
            {"Nov", "11"},
            {"Dec", "12"}
        };

        //date_str example: Sat, 20 Oct 2001 03:10:58 -0700 (PDT)    
        // Expression about was verified at http://regex101.com/r/rC1pR9
        // ([A-Z][a-z][a-z]),\s([0-9]+)\s([A-Z][a-z][a-z])\s([0-9]{4,4})\s([0-2][0-9]:[0-5][0-9]:[0-5][0-9])\s(-[0-9]{4,4})\s(\([A-Z]{3,3}\))

        const static std::string reg_exp =
                "([A-Z][a-z][a-z]),\\s([0-9]+)\\s([A-Z][a-z][a-z])\\s([0-9]{4,4})\\s([0-2][0-9]):([0-5][0-9]):([0-5][0-9])\\s(-[0-9]{4,4})\\s(\\([A-Z]{3,3}\\))";

        boost::regex date_rgx(reg_exp);
        boost::sregex_iterator it(date_str.begin(), date_str.end(), date_rgx);

        date_parsed_data["week_day"] = (*it)[1].str();

        date_parsed_data["month_day"] = (*it)[2].str().size() == 1 ?
                std::string("0") + (*it)[2].str() :
                (*it)[2].str();

        date_parsed_data["month"] = months[ (*it)[3].str() ];

        date_parsed_data["year"] = (*it)[4].str();

        date_parsed_data["hour"] = (*it)[5].str();
        date_parsed_data["minute"] = (*it)[6].str();
        date_parsed_data["second"] = (*it)[7].str();
        date_parsed_data["time_zone"] = (*it)[8].str();

        std::stringstream sstr("");
        sstr << date_parsed_data["year"] << "-"
                << date_parsed_data["month"] << "-"
                << date_parsed_data["month_day"] << " "
                << date_parsed_data["hour"] << ":"
                << date_parsed_data["minute"] << ":"
                << date_parsed_data["second"];

        try {
            date = bpt::ptime(bpt::time_from_string(sstr.str()));
        } catch (std::exception& e) {
            std::stringstream sstr;
            sstr << "Could not convert " << date_str << " to internal date format:  "
                    << "Date was parsed as : "
                    << " month == " << date_parsed_data["year"]
                    << " month_day == " << date_parsed_data["month_day"]
                    << " hour == " << date_parsed_data["hour"]
                    << " minute == " << date_parsed_data["minute"]
                    << " second == " << date_parsed_data["second"]
                    << " Exception: " << e.what();
            LOG_MESSAGE("Mail", sstr.str().c_str());
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
                    std::string rawField = std::string(
                            rawData.begin() + pos_field + field.size() + 2,
                            rawData.begin() + pos_end_field_value);

                    size_t posr = rawField.find("\r");
                    if (posr != std::string::npos) {
                        rawField.erase(posr, 1);
                    }

                    emailFields[field](rawField);
                }
            }
        } else {
            std::stringstream sstr;
            sstr << "Error Mail::parseMailData()";
            LOG_MESSAGE("Mail", sstr.str().c_str());
        }
    }

    const std::string Mail::toJSON() const {
        namespace bptree = boost::property_tree;

        bptree::ptree pt;
        pt.put("from", getFrom());

        bptree::ptree to;
        for (auto& email_to : getTo()) {
            bptree::ptree to_item;
            to_item.put("", email_to);
            to.push_back(std::make_pair("", to_item));
        }
        pt.add_child("to", to);
        pt.put("subject", getSubject());
        pt.put("messageID", getMessageID());
        pt.put("date", getISODate());

        std::stringstream sstr;
        bptree::write_json(sstr, pt, false);

        return std::move(sstr.str());
    }

    const std::string Mail::getISODate() const {
        bpt::ptime p = getDate();
        return std::move(bpt::to_iso_extended_string(p));
    }


};