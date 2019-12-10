#include <iostream>

#include <LockServer.h>

int main()
{
    LockServer ls(8080, 2);
    ls.init();
    ls.run();
}
