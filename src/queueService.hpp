#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <vector>
#include "processService.hpp"

// Service to manage the priority queue of processes.
class QueueService {
private:
    // Custom comparator to order processes by vruntime (min-heap).
    struct Compare {
        bool operator()(const Process* a, const Process* b) const {
            return a->vruntime > b->vruntime;
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, Compare> q;

public:
    QueueService() = default;

    // Pushes a process pointer onto the queue.
    void push_element(Process* p);

    // Removes the top process from the queue.
    void pop_element();

    // Checks if the queue is empty.
    bool is_empty() const;

    // Returns a pointer to the process with the lowest vruntime.
    Process* top_element();
};

#endif // QUEUE_HPP
