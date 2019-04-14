#include "../include/hobotmq.h"
#include <cstring>

namespace sunrise {

HobotMQ::HobotMQ(const char* path) : context_(NULL),
                                     zmqsock_(NULL),
                                     path_(path) {
}

HobotMQ::~HobotMQ() {
  if (zmqsock_) {
    zmq_close(zmqsock_);
    zmqsock_ = NULL;
  }

  if (context_) {
    zmq_ctx_destroy(context_);
    context_ = NULL;
  }
}

int HobotMQ::Init(MQ_TYPE type, const char* topic, MQ_PROTOCOL proto) {
  context_ = zmq_ctx_new();
  std::string addr = "";
  if (PROTO_IPC == proto)
    addr += "ipc://";
  addr += path_;
  switch (type) {
    case MQ_REQ:
      zmqsock_ = zmq_socket(context_, ZMQ_REQ);
      return zmq_connect(zmqsock_, addr.c_str());
      break;
    case MQ_REP:
      zmqsock_ = zmq_socket(context_, ZMQ_REP);
      return zmq_bind(zmqsock_, addr.c_str());
      break;
    case MQ_PUB:
      zmqsock_ = zmq_socket(context_, ZMQ_PUB);
      return zmq_bind(zmqsock_, addr.c_str());
      break;
    case MQ_SUB:
      zmqsock_ = zmq_socket(context_, ZMQ_SUB);
      if (0 != zmq_connect(zmqsock_, addr.c_str()))
        return -1;
      return zmq_setsockopt(zmqsock_, ZMQ_SUBSCRIBE, topic, strlen(topic));
      break;
    case MQ_PULL:
      zmqsock_ = zmq_socket(context_, ZMQ_PULL);
      return zmq_connect(zmqsock_, addr.c_str());
      break;
    case MQ_PUSH:
      zmqsock_ = zmq_socket(context_, ZMQ_PUSH);
      return zmq_bind(zmqsock_, addr.c_str());
      break;
    default:
      break;
  }
  return 0;
}
   
int HobotMQ::RecvMsg(char* buf, int len) {
  return zmq_recv(zmqsock_, buf, len, 0);
}

int HobotMQ::SendMsg(const char* buf, int len) {
  return zmq_send(zmqsock_, buf, len, 0);
}

const char* HobotMQ::GetErrorInfo() {
  return zmq_strerror(zmq_errno());
}

}