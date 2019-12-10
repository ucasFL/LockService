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
    std::condition_variable cv;
};

class LockServerImpl
{
public:
    LockServerImpl() {}
    LockServerImpl(const LockServerImpl &) = delete;

    void acquire(LockID lock_id, PID pid);

    void release(LockID lock_id, PID pid);

    ~LockServerImpl() {}

private:
    int n_acquire = 0;
    std::mutex mutex_lock;
    std::map<LockID, Lock> locks;
};

