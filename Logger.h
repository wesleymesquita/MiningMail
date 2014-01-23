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

namespace bpt = boost::posix_time;

class Logger{
public:
    static void log(const char* instance_name, const char* message);    
    static void initLogger(const char* instance_name, const char* fileLoc=nullptr);
    static void finalizeLogger(const char* instance_name);    
private:
    static std::unordered_map<std::string, Logger*> instances;
    static const std::string BASE_DIR;     
    
    Logger();
    std::string logFileLoc;
    std::fstream logStream;    
    bpt::ptime timestamp;
    
    void updateTimeStamp();

};


#endif	/* LOGGER_H */

