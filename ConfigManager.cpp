#include "ConfigManager.h"


const char* ConfigManager::getDefaultRootDir(){

#ifdef BOOST_OS_LINUX
    DEFAULT_ROOT_DIR = "/home/wesley";
#elif BOOST_OS_WINDOWS
    DEFAULT_ROOT_DIR = R("c:\tmp");
#else
    
#endif    
}

void ConfigManager::initConfigManager(){
    
}

ConfigManager::ConfigManager(std::string configLoc){
    
}

void ConfigManager::finalizeConfigManager(){
    
}

