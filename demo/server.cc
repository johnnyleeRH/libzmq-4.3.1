#include "tcpmq.h"
#include "usermsg.h"
#include <assert.h>
#include <string.h>
#include <iostream>

int main ()
{
    mq::tcpmq smq;
    smq.init ("", 5555, "server");
    // 长度自行调整，需要比客户端发送的报文长
    char buf[100];
    while (1) {
        smq.recvmsg(buf, 100);
        std::cout << "recv msg" << std::endl;
        assert(((UserMsg*)buf)->a == 5);
        assert(std::abs(((UserMsg*)buf)->b - 3.3) <= 1e-5);
        assert(strncmp(((UserMsg*)buf)->c, "hello", 5) == 0);
    }
    return 0;
}