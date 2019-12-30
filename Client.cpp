#include <iostream>
#include <string>
#include <thread>

#include "LockClient.h"

namespace StatusCodes
{
extern const int OK;
extern const int ERROR;
}

int share_number = 0;
LockID lock_id = 1;
void worker(PID pid)
{
    LockClient lc("localhost", 8080);
    Status s;
    for (size_t i = 0; i < 3; ++i)
    {
        s = lc.acquire(lock_id, pid);
        if (s == StatusCodes::ERROR)
        {
            std::cout << "Acquire lock " << lock_id << "failed" << std::endl;
            exit(0);
        }

        std::cout << "Pid = " << pid << ", "
                  << "share_number = " << share_number << std::endl;
        ++share_number;

        s = lc.release(lock_id, pid);
        if (s == StatusCodes::ERROR)
        {
            std::cout << "Release lock " << lock_id << "failed" << std::endl;
            exit(0);
        }
    }
}


int main()
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();
    std::cout << "The final value of share_number is " << share_number << std::endl;
    return 0;
}
