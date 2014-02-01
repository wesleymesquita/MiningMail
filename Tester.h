/* 
 * File:   Tester.h
 * Author: Wesley Mesquita
 *
 * Created on 19 de Janeiro de 2014, 19:35
 */

#ifndef TESTER_H
#define	TESTER_H

#include<string>
#include<boost/current_function.hpp>

#include "MiningMail.h"
namespace mm {

    class Tester {
    public:
        Tester(const char* className);
        bool assertStrings(const char* funtion_name,
                const char* expected,
                const char* result);
    private:
        std::string className;
        const char* FAILED = "FAILED";

    };
};

#endif	/* TESTER_H */

