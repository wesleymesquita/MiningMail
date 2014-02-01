/* 
 * File:   ConfigManager.h
 * Author: wesley
 *
 * Created on January 26, 2014, 8:39 PM
 */

#ifndef CONFIGMANAGER_H
#define	CONFIGMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

namespace mm {

    class ConfigManager {
    public:
        static void initConfigManager(const char* configFileLoc);
        static void finalizeConfigManager();
        static const char* getProperty(const char* key);

    private:

        static const char* LINUX;
        static const char* WINDOWS;
        const char* getOS();


        static std::unique_ptr<ConfigManager> instance;
        static const char* DEFAULT_ROOT_DIR;

        // private and std::unique_ptr to ensure singleton 
        ConfigManager(const char* configFileLoc); 

        std::string rootDir;
        std::unordered_map<std::string, std::string> properties;
        const char* getDefaultRootDir();

    };
}
#endif	/* CONFIGMANAGER_H */

