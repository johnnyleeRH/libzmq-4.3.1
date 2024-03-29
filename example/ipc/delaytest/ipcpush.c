#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "common.h"

int main (void)
{
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_PUSH);
    int rc = zmq_bind (responder, "ipc://xxx");
    assert (rc == 0);
    tminit(kcheckcnt);
    char buffer[10] = {0};
    // printf("buffer %s.\n", buffer);
    char sendbuf[bufsize];
    unsigned char a = 0;
    for (int i = 0; i < bufsize; ++i) {
      sendbuf[i] = (char)(a++);
    }
    int cnt = 0;
    int ret = 0;
    while (cnt < kcheckcnt) {
        gettimeofday(&cost[cnt++], NULL);
        ret = zmq_send (responder, sendbuf, bufsize, 0);
        usleep(40000);
        // printf("[%d %s]\n", ret, zmq_strerror(zmq_errno()));
        // zmq_recv (responder, buffer, 10, 0);
        // ++cnt;
    }
    zmq_close(responder);
    zmq_ctx_destroy (context);
    loggertime("/smart/zmqtest/pushtime");
    timefree();
    return 0;
}