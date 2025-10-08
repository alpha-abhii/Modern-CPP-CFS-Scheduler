#include "processService.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

PROCESS_NATURE stringToProcessNature(const std::string& nature) {
    if (nature == "CPU_BOUND") return PROCESS_NATURE::CPU_BOUND;
    if (nature == "IO_BOUND") return PROCESS_NATURE::IO_BOUND;
    throw std::invalid_argument("Invalid PROCESS_NATURE value in JSON: " + nature);
}

std::vector<Process*> getProcessFromJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    json processesJson;
    file >> processesJson;
    file.close();

    std::vector<Process*> processes;
    for (const auto& item : processesJson) {
        // NOTE: Using 'new' which is what we will refactor.
        Process* process = new Process();
        process->pid = item.at("pid");
        process->vruntime = item.at("vruntime");
        process->cpu_burst_time = item.at("cpu_burst_time");
        process->priority = item.at("priority");
        process->processState.counter = item.at("processState").at("counter");
        process->processNature = stringToProcessNature(item.at("processNature"));
        processes.push_back(process);
    }

    return processes;
}
