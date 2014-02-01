#include "ConfigManager.h"
#include "MiningMail.h"

std::unique_ptr<ConfigManager> ConfigManager::instance;
const char* ConfigManager::DEFAULT_ROOT_DIR = nullptr;

const char* ConfigManager::getDefaultRootDir() {

    if (!DEFAULT_ROOT_DIR) {
#ifdef BOOST_OS_LINUX
        DEFAULT_ROOT_DIR = "/home/wesley";
#elif BOOST_OS_WINDOWS
        DEFAULT_ROOT_DIR = R("c:\tmp");
#else
#error "OS not supported"
#endif    
    }
    return DEFAULT_ROOT_DIR;
}

void ConfigManager::initConfigManager(const char* configFileLoc) {
    if (!instance) {
        instance = std::unique_ptr<ConfigManager>(new ConfigManager(configFileLoc));
    } else {
        LOG_MESSAGE("ConfigManager", "ConfigManager already configured");
    }
}

void ConfigManager::finalizeConfigManager() {
}

const char* ConfigManager::getProperty(const char* property) {
    try{
        return instance->properties[property].c_str();
    }
    catch(const std::out_of_range& oor){
        std::stringstream sstr;
        sstr << "Could not find property:  " << property << 
                "Exception: " << oor.what();
        LOG_MESSAGE("ConfigManager", sstr.str().c_str());
    }
}

ConfigManager::ConfigManager(const char* configFileLoc) {
    bptree::ptree pt;
    bptree::read_json(configFileLoc, pt);

#ifdef BOOST_OS_LINUX
    const char* SO = "LINUX";
#elif BOOST_OS_WINDOWS
    const char* SO = "WINDOWS";
#else
#error "OS not supported"
#endif    

    try {
        
        properties["defaultRootDir"] = getDefaultRootDir();
        
        BOOST_FOREACH(bptree::ptree::value_type &v,
                pt.get_child("configs")) {
            if (v.second.get<std::string>("so").compare(SO) == 0) {
                
                pt.get_child("configs").get
                BOOST_FOREACH(bptree::ptree::value_type &w,
                        v.get_child("data")) {
                    properties[w.first] = w.second.get_value<std::string>();                
                }

               break;     
            }
        }
   
    } catch (bptree::ptree_bad_data& e) {
        LOG_MESSAGE("ConfigManager", "Could not parse config file");
    }
}