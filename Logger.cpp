#include "Logger.h"

std::unique_ptr<Logger> Logger::instance;

void Logger::log(const char* function_name,
        unsigned int line,
        const char* log_instance_name,
        const char* message) {
    
    
    bptree::ptree pt;
    pt.put("datetime", bpt::to_simple_string(bpt::second_clock::local_time()).c_str());
    pt.put("function_name", function_name);
    pt.put("line", line);
    pt.put("log_instance_name", log_instance_name);
    pt.put("message", message);
    
    bptree::write_json(instance->logStream, pt, false);
}

void Logger::initLogger(const char* fileLoc) {
    instance  = std::unique_ptr<Logger>(new Logger());

    if (fileLoc) {
        instance->logFileLoc = fileLoc;
    }else {
       instance->logFileLoc = std::string(ConfigManager::getProperty("rootDir")) + 
                std::string("/log.json");    
    }

    instance->logStream.open(instance->logFileLoc.c_str(),
            std::fstream::out | std::fstream::app);

    if (!instance->logStream.good()) {
        std::cerr << "ERROR when trying to initilize Logger" << std::endl;
        throw std::exception();
    }
}

void Logger::finalizeLogger() {
    instance->logStream.close();
}

Logger::Logger(){
    // Forces singleton     
}




