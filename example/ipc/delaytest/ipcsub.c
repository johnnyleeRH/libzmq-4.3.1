#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#include "common.h"

int main (void)
{
    int clientno = 0;
    printf("input client index.\n");
    cin >> clientno;
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_SUB);
    zmq_connect (requester, "ipc://xxx");
    zmq_setsockopt (requester, ZMQ_SUBSCRIBE, "", 0);
    // tminit(kcheckcnt);
    // zmq_send (requester, "Hello", 5, 0);
    char recvbuf[bufsize];
    int request_nbr;
    // printf("1\n");
    int ret;
    // sleep(10);
    // int result;
    printf("sub %d\n", clientno);
    // for (request_nbr = 0; request_nbr < kcheckcnt; request_nbr++) {
      while (1) {
      ret = zmq_recv (requester, recvbuf, bufsize, 0);
      if (ret < 0)
        printf("[%d %s]\n", ret, zmq_strerror(zmq_errno()));
      // gettimeofday(&cost[request_nbr], NULL);
    }
    // printf("2 %d\n", request_nbr);
    zmq_close (requester);
    zmq_ctx_destroy (context);
    char test[100] = {0};
    // snprintf(test, 100, "/smart/zmqtest/subtime%d", clientno);
    // loggertime(test);
    // timefree();
    return 0;
}