#include <iostream>

#include <LockServerImpl.h>

namespace StatusCodes
{
extern const int LOCK_FREE;
extern const int LOCK_LOCKED;
}

void LockServerImpl::acquire(LockID lock_id, PID pid)
{
    std::unique_lock<std::mutex> lock(mutex_lock);

    locks[lock_id].cv.wait(lock, [&]() { return locks[lock_id].lock_status == StatusCodes::LOCK_FREE; });
    locks[lock_id].lock_status = StatusCodes::LOCK_LOCKED;

    std::cout << "Process " << pid << " acquired lock " << lock_id << std::endl;
    ++n_acquire;
}

void LockServerImpl::release(LockID lock_id, PID pid)
{
    std::unique_lock<std::mutex> lock(mutex_lock);

    locks[lock_id].lock_status = StatusCodes::LOCK_FREE;
    --n_acquire;

    std::cout << "Process " << pid << " released lock " << lock_id << std::endl;
    locks[lock_id].cv.notify_one();
}
