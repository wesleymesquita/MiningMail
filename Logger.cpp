#include "Logger.h"

std::unordered_map<std::string, Logger*> Logger::instances;
const std::string Logger::BASE_DIR = R"(c:\tmp\)";

void Logger::log(const char* function_name,
        unsigned int line,
        const char* log_instance_name,
        const char* message) {
    
    if (instances.find(log_instance_name) == instances.end()) {
        initLogger(log_instance_name);
    }

    bptree::ptree pt;
    pt.put("datetime", bpt::to_simple_string(bpt::second_clock::local_time()).c_str());
    pt.put("function_name", function_name);
    pt.put("line", line);
    pt.put("log_instance_name", log_instance_name);
    pt.put("message", message);
    
    bptree::write_json(instances[log_instance_name]->logStream, pt, false);
}

void Logger::initLogger(const char* instance_name,
        const char* fileLoc) {

    instances[instance_name] = new Logger();

    if (!fileLoc) {
        instances[instance_name]->logFileLoc = BASE_DIR + instance_name + ".log";
    } else {
        instances[instance_name]->logFileLoc = fileLoc;
    }


    instances[instance_name]->logStream.open(
            instances[instance_name]->logFileLoc.c_str(),
            std::fstream::out | std::fstream::app);

    if (!instances[instance_name]->logStream.good()) {
        throw std::exception();
    }
}

void Logger::finalizeLogger(const char* instance_name) {
    instances[instance_name]->logStream.close();
    delete instances[instance_name];
}

Logger::Logger() {
    // Forces singleton     
}

void Logger::updateTimeStamp() {
    timestamp = bpt::second_clock::local_time();
}



