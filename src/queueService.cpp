#include "queueService.hpp"

void QueueService::push_element(Process* p) {
    q.push(p);
}

void QueueService::pop_element() {
    q.pop();
}

bool QueueService::is_empty() const {
    return q.empty();
}

Process* QueueService::top_element() {
    return q.top();
}
