/* 
 * File:   MiningMail.h
 * Author: wesley
 *
 * Created on January 31, 2014, 9:00 PM
 */

#ifndef MININGMAIL_H
#define	MININGMAIL_H

#include<boost/current_function.hpp>
#include "Logger.h"

namespace mm {

#define LOG_MESSAGE(__LOG_ID__, __LOG_MESSAGE__)\
   mm::Logger::log(BOOST_CURRENT_FUNCTION, __LINE__, __LOG_ID__, __LOG_MESSAGE__); 
};

#endif	/* MININGMAIL_H */
