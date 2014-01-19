#include "Logger.h"

Logger* Logger::instance = nullptr;

void Logger::log(const char* message){
    std::stringstream sstr;
    sstr << "[Mining Mail]" << message << std::endl;
    instance->logStream.write(sstr.str().c_str(), 512) ;
}    

void Logger::initLogger(const char* fileLoc){
    instance = new Logger();     
    instance->logStream.open(fileLoc, std::fstream::out | std::fstream::app);
    if( !instance->logStream.good() ){
        instance->logStream.open("log.tmp", std::fstream::out | std::fstream::app);            
    }
}    

void Logger::finalizeLogger(){
    instance->logStream.close();
    delete instance;
}        

Logger::Logger(){
   // Forces singleton     
}    


