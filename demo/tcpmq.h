#pragma once

#include "zmq.h"
#include <string>
#include <iostream>

namespace mq
{

#define CHECK_RET(opr, ret)                                                    \
    {                                                                          \
        if (-1 == ret) {                                                       \
            std::cout << opr << " failed: " << zmq_strerror (zmq_errno ())     \
                      << std::endl;                                            \
        }                                                                      \
    }

class tcpmq
{
  public:
    tcpmq () : context_ (nullptr), sock_ (nullptr){};
    virtual void init (const std::string &ip, int port, const std::string &attr)
    {
        context_ = zmq_ctx_new ();
        char cport[10] = {0};
        snprintf (cport, 10, "%d", port);
        if (attr == "client") {
            sock_ = zmq_socket (context_, ZMQ_REQ);
            std::string remote = "tcp://" + ip + ":";
            remote = remote + std::string (cport);
            CHECK_RET ("connect", zmq_connect (sock_, remote.c_str ()))
        } else {
            sock_ = zmq_socket (context_, ZMQ_REP);
            std::string svr = "tcp://*:" + std::string (cport);
            CHECK_RET ("bind", zmq_bind (sock_, svr.c_str ()))
        }
    }
    virtual int recvmsg (char *buf, int len)
    {
        return zmq_recv (sock_, buf, len, 0);
    }
    virtual int sendmsg (const char *buf, int len)
    {
        return zmq_send (sock_, buf, len, 0);
    }
    virtual ~tcpmq ()
    {
        if (sock_) {
            zmq_close (sock_);
            sock_ = nullptr;
        }

        if (context_) {
            zmq_ctx_destroy (context_);
            context_ = nullptr;
        }
    };

  private:
    void *context_;
    void *sock_;
};

}