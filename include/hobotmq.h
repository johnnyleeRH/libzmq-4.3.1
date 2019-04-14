#ifndef SUNRISE_HOBOT_MQ_H
#define SUNRISE_HOBOT_MQ_H

#include "../include/zmq.h"
#include <string>

namespace sunrise {
  //supported mq type till now
  enum MQ_TYPE {
    MQ_REQ,
    MQ_REP,
    MQ_PUB,
    MQ_SUB,
    MQ_PULL,
    MQ_PUSH,
  };

  //supported mq protocol till now
  enum MQ_PROTOCOL {
    PROTO_IPC,
  };

  
  #define EXPORT __attribute__((visibility("default")))
  class EXPORT HobotMQ {
    public:
      /*
      *@path: both sides of communication share the same path
      */
      explicit HobotMQ(const char* path);
      virtual ~HobotMQ();
      /*
      *init mq
      *@type: MQ_TYPE, MQ_REQ<->MQ_REP,MQ_PUB<->MQ_SUB,MQ_PULL<->MQ_PUSH
      *@topic: if type is MQ_SUB, use topic as filter, other type not care of topic
      *@proto: just use PROTO_IPC as default now
      *@ret：0 success, -1 failed.
        if ret -1, use  GetErrorInfo to get the error msg.
      */
      virtual int Init(MQ_TYPE type, const char* topic = "", MQ_PROTOCOL proto = PROTO_IPC);
      /*
       *recv msg
       *@buf: user buf
       *@len: user buf len
       *@ret：return the actual size user recved.
        if ret -1, use  GetErrorInfo to get the error msg.
      */
      virtual int RecvMsg(char* buf, int len);
      /*
       *send msg
       *@buf: user buf
       *@len: actual len want to send
       *@ret：return the actual len user send.
        if ret -1, use  GetErrorInfo to get the error msg.
      */
      virtual int SendMsg(const char* buf, int len);
      /*
      *get the error msg while error happen.
      */
      virtual const char* GetErrorInfo();

    private:
      void *context_;
      void *zmqsock_;
      std::string path_;
  };

}

#endif