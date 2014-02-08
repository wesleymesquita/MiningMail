/* 
 * File:   Tester.h
 * @Author: Wesley Mesquita
 * @email: wesleymesquita@gmail.com
 * 
 * Created Jan 19, 2014
 * Updated: Fev 08, 2014
 */

#ifndef TESTER_H
#define	TESTER_H

#include<string>
#include<functional>
#include<unordered_map>
#include<utility>
#include<algorithm>

#include<boost/property_tree/ptree.hpp>

#include "MiningMail.h"

namespace mm {
    /** @brief Tester is a framework to handle simple testing tasks
     *  A test class must inherits from Tester and implement
     *  test function that fits in std::function<bool()>
     *  
     * 
     */
    class Tester {
    public:
        /**
         * @note className is just a identifier for a set of tests, 
         *        could not be a c++ class name.   
         */
        Tester(const char* className);
        
        /**
         * @param funcName Function name that is tested
         * 
         */
        void addTestFunction(const std::string& funcName, std::function<bool()>);
        
        /**
         *  @brief runs all test functions added
         */
        bool execTest();
        
        /**
         *  @brief cleans result vector
         */
        void cleanTestResults();        
        
        /**
         *  @brief gets a JSON string with test results: the final result and 
         *         each function (in case of a fail, the user can identify where
         *         it happened)        
         */
        std::string getDetailResult();
        
        
        /**
         * @brief get the overall result
         */
        bool getFinalResult() const;
    private:
        std::string className;
        std::vector<std::string> funcs;
        std::unordered_map<std::string, std::function<bool()>> test_functions;
        std::unordered_map<std::string, bool> results;
    };
};

#endif	/* TESTER_H */

