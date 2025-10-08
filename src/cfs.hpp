#ifndef CFS_HPP
#define CFS_HPP

#include <vector>
#include "processService.hpp"
#include "processLog.hpp"

// Forward declaration
class QueueService;

// The main scheduler class that orchestrates the simulation.
class cfs {
private:
    // Creates a log entry for a process execution slice.
    void createProcessLog(std::vector<ProcessLog*>& logs, long long startTime, long long endTime, int pid);

public:
    // Runs the CFS simulation on a list of processes.
    std::vector<ProcessLog*> schedule(std::vector<Process*>& processList);
};

#endif // CFS_HPP
