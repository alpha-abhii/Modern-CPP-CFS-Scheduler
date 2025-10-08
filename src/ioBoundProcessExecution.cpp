#include "ioBoundProcessExecution.hpp"
#include <thread>
#include <chrono>

#include "cpuBoundProcessExecution.hpp" // For weightFunction

// NICE_0_LOAD is the weight of a process with a 'nice' value of 0 in the Linux kernel.
constexpr int NICE_0_LOAD = 1024;

void handleIoBoundProcess(Process* process, int ioWaitTime, QueueService& q) {
    // Simulate I/O wait by sleeping the thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(ioWaitTime));
    
    // Calculate the weight of the process.
    const double weight = weightFunction(process->priority);

    // Penalize vruntime for the I/O wait period. This is a key part of CFS.
    process->vruntime += (static_cast<long long>(ioWaitTime) * NICE_0_LOAD) / weight;
    
    // After I/O, simulate a short CPU burst (1 time slice).
    const int executedTime = 1;
    if (process->cpu_burst_time > 0) {
        process->cpu_burst_time -= executedTime;
        
        // Update vruntime for the short CPU portion.
        process->vruntime += (static_cast<long long>(executedTime) * NICE_0_LOAD) / weight;
    }
    
    // If the process is not finished, re-queue it.
    if (process->cpu_burst_time > 0) {
        q.push_element(process);
    }
}
