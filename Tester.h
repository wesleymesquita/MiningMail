/* 
 * File:   Tester.h
 * Author: Wesley Mesquita
 *
 * Created on 19 de Janeiro de 2014, 19:35
 */

#ifndef TESTER_H
#define	TESTER_H

#include<string>
#include "Logger.h"

class Tester{
public:
    Tester(const char* className);
    void assertStrings(const char* expected, const char* result);
private:    
    std::string className;
    const char* FAILED = "FAILED";
        
};

#endif	/* TESTER_H */

