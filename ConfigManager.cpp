#include "ConfigManager.h"
#include "Logger.h"

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

    
void ConfigManager::setRootDir(const char* dir){
    rootDir = dir;
}
    

void ConfigManager::initConfigManager(const char* configFileLoc){
    if(!instance){
        instance = new ConfigManager(configFileLoc);
    }
    else{
        Logger::log(BOOST_CURRENT_FUNCTION, 
                __LINE__, 
                "ConfigManager",
                "ConfigManager already configured");
    }
}

void ConfigManager::finalizeConfigManager(){
    if(instance){
        delete instance;
        //just to make sure other static 
        // call of finalizeConfigManager won double delete
        instance = nullptr_t; 
    }
}

ConfigManager::ConfigManager(const std::string& configLoc) {
    bptree::ptree pt;
    bptree::read_json(configLoc, pt);
    try {
        char* root_dir[256];
        pt.get_child("rootDir", root_dir);
        setRootDir(root_dir);
    }catch(bptree::ptree_bad_data& e){
       setRootDir(getDefaultRootDir()); 
    }    
}


