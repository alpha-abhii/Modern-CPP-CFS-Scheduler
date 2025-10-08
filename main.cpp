#include <fstream>
#include <iostream>
#include <vector>

#include "src/cfs.hpp"
#include "src/processLog.hpp"
#include "src/processService.hpp"

int main() {
    // 1. Load processes from the JSON file.
    // NOTE: This uses raw pointers, which we will refactor.
    std::vector<Process*> processes = getProcessFromJson("resources/process.json");

    // 2. Create the scheduler and run the simulation.
    cfs scheduler;
    std::vector<ProcessLog*> logs = scheduler.schedule(processes);

    // 3. Write the simulation logs to a CSV file.
    std::ofstream outFile("process_schedule.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open process_schedule.csv for writing." << std::endl;
        return 1;
    }
    
    outFile << "pid,start_time,end_time" << std::endl;

    for (const auto* processLog : logs) {
        outFile << processLog->pid << ","
                << processLog->startTime << ","
                << processLog->endTime << std::endl;
    }

    outFile.close();

    // 4. Clean up allocated memory.
    // NOTE: This manual cleanup is what we will eliminate with smart pointers.
    for (auto* log : logs) {
        delete log;
    }
    for (auto* process : processes) {
        delete process;
    }

    std::cout << "CFS simulation complete. Output written to process_schedule.csv" << std::endl;
    std::cout << "Run 'python3 plot.py' to visualize the schedule." << std::endl;

    return 0;
}
