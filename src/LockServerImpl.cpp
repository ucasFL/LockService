#include <iostream>

#include <LockServerImpl.h>

namespace StatusCodes
{
extern const int OK;
extern const int LOCK_FREE;
extern const int LOCK_LOCKED;
extern const int SERVER_BUSY;
}

Status LockServerImpl::acquire(LockID lock_id, PID pid)
{
    Status ret = StatusCodes::OK;
    // here can not happen dead lock
    // get mutex_lock failed implies another active thread is working
    std::unique_lock<std::mutex> lock(mutex_lock);

    // avoid server happens dead lock
    // do not let all thread blocked
    if (locks[lock_id].lock_status == StatusCodes::LOCK_LOCKED)
    {
        if (inactive_worker == thread_num - 1)
            return StatusCodes::SERVER_BUSY;
        ++inactive_worker;
    }

    locks[lock_id].cv.wait(lock, [&]() { return locks[lock_id].lock_status == StatusCodes::LOCK_FREE; });
    locks[lock_id].lock_status = StatusCodes::LOCK_LOCKED;
    locks[lock_id].pid = pid;

    if (inactive_worker > 0)
    {
        --inactive_worker;
    }

    std::cout << "Process " << pid << " acquired lock " << lock_id << std::endl;
    ++n_acquire;
    return ret;
}

Status LockServerImpl::release(LockID lock_id, PID pid)
{
    Status ret = StatusCodes::OK;
    std::unique_lock<std::mutex> lock(mutex_lock);

    locks[lock_id].lock_status = StatusCodes::LOCK_FREE;
    --n_acquire;

    std::cout << "Process " << pid << " released lock " << lock_id << std::endl;
    locks[lock_id].cv.notify_all();

    return ret;
}
