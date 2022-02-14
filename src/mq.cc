#include "mq.h"
#include "tcpmq.h"

MQ *MQ::GetInst ()
{
    static TCPMQ tcpmq;
    return &tcpmq;
}

MQ::~MQ ()
{
}