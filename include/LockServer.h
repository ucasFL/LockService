#pragma once

#include <memory>

#include <rpc/server.h>

#include <LockServerImpl.h>


class LockServer
{
public:
    LockServer()
    {
        ls_impl = std::make_unique<LockServerImpl>();
        rs_ptr = std::make_unique<rpc::server>(d_port);
    }

    LockServer(const LockServer &) = delete;

    LockServer(Port d_port_) : d_port(d_port_)
    {
        ls_impl = std::make_unique<LockServerImpl>();
        rs_ptr = std::make_unique<rpc::server>(d_port);
    }

    LockServer(Port d_port_, size_t thread_num_) : d_port(d_port_), thread_num(thread_num_)
    {
        ls_impl = std::make_unique<LockServerImpl>(thread_num);
        rs_ptr = std::make_unique<rpc::server>(d_port);
    }

    void init();
    void run();

    ~LockServer() {}

private:
    Port d_port = 8080;
    size_t thread_num = 2;
    std::unique_ptr<rpc::server> rs_ptr;
    std::unique_ptr<LockServerImpl> ls_impl;
};

