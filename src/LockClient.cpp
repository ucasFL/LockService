#include <iostream>

#include <LockClient.h>

namespace StatusCodes
{
extern const int OK;
extern const int ERROR;
extern const int SERVER_BUSY;
}

Status LockClient::acquire(LockID lock_id, PID pid) const
{
    try
    {
        Status ret;
        ret = clt->call("acquire", lock_id, pid).as<Status>();
        while (ret == StatusCodes::SERVER_BUSY)
            ret = clt->call("acquire", lock_id, pid).as<Status>();
        return ret;
    }
    catch (rpc::rpc_error & _)
    {
        std::cout << "Process " << pid << "acquire lock " << lock_id << "failed" << std::endl;
        return StatusCodes::ERROR;
    }
}

Status LockClient::release(LockID lock_id, PID pid) const
{
    try
    {
        Status ret;
        ret = clt->call("release", lock_id, pid).as<Status>();
        return ret;
    }
    catch (rpc::rpc_error & _)
    {
        std::cout << "Process " << pid << "release lock " << lock_id << "failed" << std::endl;
        return StatusCodes::ERROR;
    }
}
