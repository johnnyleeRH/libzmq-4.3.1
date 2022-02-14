#pragma once

#include "mq.h"

class TCPMQ : public MQ
{
  public:
    TCPMQ () : context_ (nullptr), sock_ (nullptr){};
    virtual void
    Init (const std::string &ip, int port, const std::string &attr);
    virtual int RecvMsg (char *buf, int len);
    virtual int SendMsg (const char *buf, int len);
    virtual ~TCPMQ ();

  private:
    void *context_;
    void *sock_;
};