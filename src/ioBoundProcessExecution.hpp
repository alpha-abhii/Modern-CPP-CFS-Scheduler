#ifndef IO_BOUND_PROCESS_EXECUTION_HPP
#define IO_BOUND_PROCESS_EXECUTION_HPP

#include "processService.hpp"
#include "queueService.hpp"

// Simulates the execution of an I/O-bound process.
void handleIoBoundProcess(Process* process, int ioWaitTime, QueueService& q);

#endif // IO_BOUND_PROCESS_EXECUTION_HPP
