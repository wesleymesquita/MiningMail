/* 
 * File:   Logger.h
 * Author: Wesley Mesquita
 *
 * Created on 19 de Janeiro de 2014, 17:13
 */

#ifndef LOGGER_H
#define	LOGGER_H
#include<string>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

#include "ConfigManager.h"

namespace bpt = boost::posix_time;
namespace bptree = boost::property_tree;
class Logger{
public:
    static void log(const char* function_name, 
            unsigned int line,
            const char* log_instance_name, 
            const char* message);    
    static void initLogger(const char* instance_name, const char* fileLoc=nullptr);
    static void finalizeLogger(const char* instance_name);    
private:
    static std::unordered_map<std::string, Logger*> instances;
    
    Logger();
    std::string logFileLoc;
    std::fstream logStream;    
    bpt::ptime timestamp;
    const std::string BASE_DIR;        
    void updateTimeStamp();

};


#endif	/* LOGGER_H */

