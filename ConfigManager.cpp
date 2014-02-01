#include<string>
#include<memory>
#include<unordered_map>
#include<stdexcept>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include<boost/predef.h>
#include<boost/foreach.hpp>

#include "ConfigManager.h"
#include "MiningMail.h"

namespace mm {

    namespace bptree = boost::property_tree;

    std::unique_ptr<ConfigManager> ConfigManager::instance;
    const char* ConfigManager::DEFAULT_ROOT_DIR = nullptr;
    const char* ConfigManager::LINUX = "LINUX";
    const char* ConfigManager::WINDOWS = "WINDOWS";

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
        try {
            return instance->properties[property].c_str();
        } catch (const std::out_of_range& oor) {
            std::stringstream sstr;
            sstr << "Could not find property:  " << property <<
                    "Exception: " << oor.what();
            LOG_MESSAGE("ConfigManager", sstr.str().c_str());
        }
    }

    const char* ConfigManager::getOS() {
#ifdef BOOST_OS_LINUX
        return ConfigManager::LINUX;
#elif BOOST_OS_WINDOWS
        return ConfigManager::WINDOWS;
#else
#error "OS not supported"
#endif    

    }

    ConfigManager::ConfigManager(const char* configFileLoc) {

        bptree::ptree pt;
        bptree::read_json(configFileLoc, pt);

        const char* currentOS = getOS();

        properties["defaultRootDir"] = getDefaultRootDir();

        try {

            BOOST_FOREACH(bptree::ptree::value_type &v,
                    pt.get_child("configs")) {

                if (v.second.get<std::string>("so").compare(currentOS) == 0) {

                    BOOST_FOREACH(bptree::ptree::value_type &w,
                            v.second.get_child("data")) {

                        properties[w.first] = w.second.get_value<std::string>();
                    }

                    break;
                }
            }

        } catch (bptree::ptree_bad_data& e) {
            LOG_MESSAGE("ConfigManager", "Could not parse config file");
        }
    }
};