#include "mq.h"
#include "usermsg.h"
#include <string.h>
#include <unistd.h>
#include <iostream>

int main ()
{
    UserMsg msg;
    MQ *mq = MQ::GetInst ();
    mq->Init ("10.78.4.150", 5555, "client");
    while (1) {
        msg.a = 5;
        msg.b = 3.3;
        memset (msg.c, 0, 50);
        memcpy (msg.c, "hello", 5);
        mq->SendMsg ((char *) &msg, sizeof (msg));
        std::cout << "send msg" << std::endl;
    }
    return 0;
}