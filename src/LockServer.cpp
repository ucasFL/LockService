#include <iostream>

#include <LockServer.h>

void LockServer::init()
{
    rs_ptr->bind("acquire", [&](LockID lock_id, PID pid) { ls_impl->acquire(lock_id, pid); });
    rs_ptr->bind("release", [&](LockID lock_id, PID pid) { ls_impl->release(lock_id, pid); });
}


void LockServer::run()
{
    rs_ptr->async_run(thread_num);
    std::cin.ignore();
}
