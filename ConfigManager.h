/* 
 * File:   ConfigManager.h
 * Author: wesley
 *
 * Created on January 26, 2014, 8:39 PM
 */

#ifndef CONFIGMANAGER_H
#define	CONFIGMANAGER_H

#include<string>
#include<memory>
#include<unordered_map>
#include<stdexcept>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include<boost/predef.h>
#include<boost/foreach.hpp>


namespace bptree = boost::property_tree;

class ConfigManager{
public:
    static void initConfigManager(const char* configFileLoc);
    static void finalizeConfigManager();
    static const char* getProperty(const char* key);
private:
    static std::unique_ptr<ConfigManager> instance;
    static const char* DEFAULT_ROOT_DIR;
      
    ConfigManager(const char* configFileLoc);   //ensures singleton 
    
    std::string rootDir;
    std::unordered_map<std::string, std::string> properties;
    const char* getDefaultRootDir();
};

#endif	/* CONFIGMANAGER_H */

