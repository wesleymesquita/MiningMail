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

namespace bptree = boost::property_tree;

class ConfigManager{
public:
    static const char* getDefaultRootDir();
    static void initConfigManager(const char* configFileLoc);
    static void finalizeConfigManager();
private:
    static ConfigManager* instance;
    static const char* DEFAULT_ROOT_DIR;

    ConfigManager(const std::string& configLoc);   //ensures singleton 
    void setRootDir(const char* dir);
    std::string rootDir;
};

#endif	/* CONFIGMANAGER_H */

