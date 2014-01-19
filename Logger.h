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

class Logger{
public:
    static void log(const char* message);    
    static void initLogger(const char* fileLoc);
    static void finalizeLogger(const char* fileLoc);    
private:
    static Logger *instance;
        
    Logger();
    std::string logFileLoc;
    std::ifstream logStream;    
};


#endif	/* LOGGER_H */

