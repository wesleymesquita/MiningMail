#include "Logger.h"

std::unordered_map<std::string, Logger*> Logger::instances;
const std::string Logger::BASE_DIR = R"(c:\tmp\)";

void Logger::log(const char* instance_name, const char* message) {
    if (instances.find(instance_name) == instances.end()) {
        initLogger(instance_name);
    }

    std::stringstream sstr;
    sstr << "[Mining Mail]" << message << std::endl;
    instances[instance_name]->logStream.write(sstr.str().c_str(), sstr.str().size());
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


