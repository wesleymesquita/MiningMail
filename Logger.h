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
#include<memory>

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
    static void initLogger(const char* fileLoc=nullptr);
    static void finalizeLogger();    

private:
    static std::unique_ptr<Logger> instance;
    
    Logger();
    std::string logFileLoc;
    std::fstream logStream;    

};


#endif	/* LOGGER_H */

