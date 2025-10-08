#ifndef CPU_BOUND_PROCESS_EXECUTION_HPP
#define CPU_BOUND_PROCESS_EXECUTION_HPP

#include "processService.hpp"
#include "queueService.hpp"

// Calculates the weight of a process based on its priority.
double weightFunction(int priority);

// Simulates the execution of a CPU-bound process for one time slice.
void executeCpuBoundProcess(Process* process, int timeSlice, QueueService& q);

#endif // CPU_BOUND_PROCESS_EXECUTION_HPP
