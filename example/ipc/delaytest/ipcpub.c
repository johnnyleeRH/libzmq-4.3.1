#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "common.h"

int main (void)
{
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (responder, "ipc://xxx");
    assert (rc == 0);
    // tminit(kcheckcnt);
    char buffer[10] = {0};
    // zmq_recv (responder, buffer, 10, 0);
    // printf("buffer %s.\n", buffer);
    char sendbuf[bufsize];
    unsigned char a = 0;
    for (int i = 0; i < bufsize; ++i) {
      sendbuf[i] = (char)(a++);
    }
    int cnt = 0;
    int ret = 0;
    sleep(10);
    printf("pub\n");
    while (1) {
        // memcpy(sendbuf, (char*)&cnt, 4);
        // gettimeofday(&cost[cnt++], NULL);
        ret = zmq_send (responder, sendbuf, bufsize, 0);
        // printf("[%d %d %s]\n", cnt - 1, ret, zmq_strerror(zmq_errno()));
        // zmq_recv (responder, buffer, 10, 0);
        usleep(40000);
    }
    // sleep(10);
    // loggertime("/smart/zmqtest/pubtime");
    zmq_close (responder);
    zmq_ctx_destroy (context);
    return 0;
}