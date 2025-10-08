#include "cfs.hpp"
#include <chrono>
#include "queueService.hpp"
#include "cpuBoundProcessExecution.hpp"
#include "ioBoundProcessExecution.hpp"

void cfs::createProcessLog(std::vector<ProcessLog*>& logs, long long startTime, long long endTime, int pid) {
    // NOTE: Using 'new' which we will refactor.
    ProcessLog* p = new ProcessLog();
    p->pid = pid;
    p->startTime = startTime;
    p->endTime = endTime;
    logs.push_back(p);
}

std::vector<ProcessLog*> cfs::schedule(std::vector<Process*>& processList) {
    QueueService queue;
    std::vector<ProcessLog*> logs;

    for (auto* process : processList) {
        queue.push_element(process);
    }

    while (!queue.is_empty()) {
        Process* process = queue.top_element();
        queue.pop_element();

        auto startTime = std::chrono::steady_clock::now();

        if (process->processNature == PROCESS_NATURE::CPU_BOUND) {
            executeCpuBoundProcess(process, 1, queue);
        } else {
            handleIoBoundProcess(process, 10, queue);
        }

        auto endTime = std::chrono::steady_clock::now();

        // Record duration in nanoseconds for precision.
        long long startTimeNs = std::chrono::duration_cast<std::chrono::nanoseconds>(startTime.time_since_epoch()).count();
        long long endTimeNs = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime.time_since_epoch()).count();

        createProcessLog(logs, startTimeNs, endTimeNs, process->pid);
    }

    return logs;
}
