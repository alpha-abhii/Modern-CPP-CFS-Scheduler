#ifndef PROCESS_LOG_HPP
#define PROCESS_LOG_HPP

// A simple struct to hold the log data for one execution slice.
struct ProcessLog {
    int pid;
    long long startTime;
    long long endTime;
};

#endif // PROCESS_LOG_HPP
