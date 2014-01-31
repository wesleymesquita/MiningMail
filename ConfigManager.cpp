#include "ConfigManager.h"
#include "MiningMail.h"

ConfigManager* ConfigManager::instance = nullptr;
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
        instance =  nullptr; 
    }
}

const char* ConfigManager::getRootDir(){
    if(instance){
        return instance->rootDir.c_str();
    }
    else{
        Logger::log(BOOST_CURRENT_FUNCTION, 
                __LINE__, 
                "ConfigManager",
                "ConfigManager not configured");
    }
}

ConfigManager::ConfigManager(const std::string& configLoc) {
    bptree::ptree pt;
    bptree::read_json(configLoc, pt);

#ifdef BOOST_OS_LINUX
    const char* SO = "LINUX";
#elif BOOST_OS_WINDOWS
    const char* SO = "WINDOWS";
#else
#error "OS not supported"
#endif    
    
    try {
        std::string root_dir;
        
        BOOST_FOREACH(bptree::ptree::value_type &v, 
                pt.get_child("configs")){
            if( v.second.get<std::string>("so").compare(SO) == 0){
              root_dir = v.second.get<std::string>("rootDir");
            }
        } 
        setRootDir(root_dir.c_str());
    }catch(bptree::ptree_bad_data& e){
       setRootDir(getDefaultRootDir()); 
    }    
}



