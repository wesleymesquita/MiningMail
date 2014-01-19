
#include "Logger.h"

void Logger::log(const char* message){
    instance->logStream << "[Mining Mail]" << message << std::endl;
    instance->logStream.
}    

void Logger::initLogger(const char* fileLoc){
    instance = new Logger();     
    instance->logStream.open(fileLoc, std::fstream::app);
    if( !instance->logStream.good() ){
        instance->logStream.open("log.tmp", std::fstream::app);            
    }
}    

void Logger::finalizeLogger(){
    instance->logStream.close();
    delete instance;
}        

Logger::Logger(){
   // Forces singleton     
}    


