/* 
 * File:   ConfigManager.h
 * Author: wesley
 *
 * Created on January 26, 2014, 8:39 PM
 */

#ifndef CONFIGMANAGER_H
#define	CONFIGMANAGER_H

#include<string>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include<boost/predef.h>

class ConfigManager{
public:
    static const char* getDefaultRootDir();
    static initConfigManager();
    static finalizeConfigManager();
private:
    ConfigManager(std::string configLoc);   //ensures singleton 
    const char* DEFAULT_ROOT_DIR;
    ConfigManager* instance;
};

#endif	/* CONFIGMANAGER_H */

