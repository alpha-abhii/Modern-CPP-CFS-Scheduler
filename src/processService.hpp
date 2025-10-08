#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

// Enum to define the nature of the process
enum class PROCESS_NATURE {
    CPU_BOUND,
    IO_BOUND
};

// Represents the state of a process, currently just a counter.
struct ProcessState {
    long long counter;
};

// Main struct representing a process in the simulation
struct Process {
    int pid;
    long long int vruntime;
    int cpu_burst_time;
    int priority;
    ProcessState processState;
    PROCESS_NATURE processNature;
};

// Converts a string from JSON to the PROCESS_NATURE enum
PROCESS_NATURE stringToProcessNature(const std::string& nature);

// Parses the process.json file and returns a vector of raw Process pointers
std::vector<Process*> getProcessFromJson(const std::string& filePath);

#endif // PROCESS_HPP
