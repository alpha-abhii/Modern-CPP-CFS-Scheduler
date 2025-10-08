#include "cpuBoundProcessExecution.hpp"
#include <algorithm> // For std::min

// NICE_0_LOAD is the weight of a process with a 'nice' value of 0 in the Linux kernel.
constexpr int NICE_0_LOAD = 1024;

double weightFunction(int priority) {
    // A simplified weight calculation. Higher priority (lower number) means higher weight.
    return static_cast<double>(NICE_0_LOAD) / (static_cast<double>(priority) + 1.0);
}

void executeCpuBoundProcess(Process* process, int timeSlice, QueueService& q) {
    const int executedTime = std::min(timeSlice, process->cpu_burst_time);
    
    process->cpu_burst_time -= executedTime;
    
    // Update vruntime based on executed time and weight.
    const double weight = weightFunction(process->priority);
    process->vruntime += (static_cast<long long>(executedTime) * NICE_0_LOAD) / weight;
    
    // If the process is not finished, re-queue it.
    if (process->cpu_burst_time > 0) {
        q.push_element(process);
    }
}
