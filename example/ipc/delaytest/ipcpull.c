#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"

int main (void)
{
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_PULL);
    zmq_connect (requester, "ipc://xxx");
    tminit(kcheckcnt);
    // zmq_send (requester, "Hello", 5, 0);
    char recvbuf[bufsize];
    int request_nbr;
    // printf("1\n");
    int ret;
    // sleep(10);
    for (request_nbr = 0; request_nbr < kcheckcnt; request_nbr++) {
      // while (1) {
      ret = zmq_recv (requester, recvbuf, bufsize, 0);
      gettimeofday(&cost[request_nbr], NULL);
      // if (ret > 0)
      //   break;
      // }
      // printf("[%d ： %d : %s]\n", request_nbr, ret, zmq_strerror(zmq_errno()));
      // gettimeofday(&cost[request_nbr], NULL);
      // zmq_send (requester, "Hello", 5, 0);
    }
    // printf("2 %d\n", request_nbr);
    zmq_close (requester);
    zmq_ctx_destroy (context);
    loggertime("/smart/zmqtest/pulltime");
    timefree();
    return 0;
}