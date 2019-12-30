#pragma once

#include <condition_variable>
#include <map>
#include <mutex>

#include <define.h>

namespace StatusCodes
{
extern const int LOCK_FREE;
}

struct Lock
{
    Status lock_status = StatusCodes::LOCK_FREE;
    PID pid;
    std::condition_variable cv;
};

class LockServerImpl
{
public:
    LockServerImpl() {}
    LockServerImpl(const size_t thread_num_) : thread_num(thread_num_) {}
    LockServerImpl(const LockServerImpl &) = delete;

    Status acquire(LockID lock_id, PID pid);

    Status release(LockID lock_id, PID pid);

    ~LockServerImpl() {}

private:
    int n_acquire = 0;
    int inactive_worker = 0;
    size_t thread_num = 2;
    std::mutex mutex_lock;
    std::map<LockID, Lock> locks;
};

