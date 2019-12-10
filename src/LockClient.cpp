#include <iostream>

#include <LockClient.h>

namespace StatusCodes
{
extern const int ACQUIRE_LOCK_OK;
extern const int ACQUIRE_LOCK_ERROR;
extern const int RELEASE_LOCK_OK;
extern const int RELEASE_LOCK_ERROR;
}

Status LockClient::acquire(LockID lock_id, PID pid) const
{
    try
    {
        clt->call("acquire", lock_id, pid);
        return StatusCodes::ACQUIRE_LOCK_OK;
    }
    catch (rpc::rpc_error & _)
    {
        std::cout << "Process " << pid << "acquire lock " << lock_id << "failed" << std::endl;
        return StatusCodes::ACQUIRE_LOCK_ERROR;
    }
}

Status LockClient::release(LockID lock_id, PID pid) const
{
    try
    {
        clt->call("release", lock_id, pid);
        return StatusCodes::RELEASE_LOCK_OK;
    }
    catch (rpc::rpc_error & _)
    {
        std::cout << "Process " << pid << "release lock " << lock_id << "failed" << std::endl;
        return StatusCodes::RELEASE_LOCK_ERROR;
    }
}
