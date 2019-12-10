#pragma once

#include <memory>
#include <string>

#include <rpc/client.h>
#include <rpc/rpc_error.h>

#include <define.h>

class LockClient
{
public:
    LockClient() = delete;
    LockClient(const LockClient &) = delete;

    LockClient(const std::string & dst_, Port d_port_) : dst(dst_), d_port(d_port_) { clt = std::make_unique<rpc::client>(dst, d_port); };

    Status acquire(LockID lock_id, PID pid) const;

    Status release(LockID lock_id, PID pid) const;

private:
    std::string dst;
    Port d_port;
    std::unique_ptr<rpc::client> clt;
};
