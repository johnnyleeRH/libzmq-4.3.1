#pragma once

#include <string>

class MQ
{
  public:
    /*
   *desc:获取消息实例，每个程序获取一次
   */
    static MQ *GetInst ();
    virtual ~MQ ();
    /*
    *desc: 初始化操作，tcp连接需要的IP PORT及client/server类型
    * @ip: 对于客户端来说，需要的服务端IP；服务端的话，ip赋值为""
    * @port: 对于客户端为需要连接的服务端port； 服务端的话，为监听端口
    * @attr: 为 client 或者 server
    */
    virtual void
    Init (const std::string &ip, int port, const std::string &attr) = 0;
    /*
       *desc: 接收消息
       *@buf: 用户内存区
       *@len: 用户内存区长度，需要大于等于预期收到的数据长度
       *@ret： 返回实际收到的字节数，如果返回-1，则有error发生
      */
    virtual int RecvMsg (char *buf, int len) = 0;
    /*
       *desc: 发送消息
       *@buf: 用户内存区
       *@len: 实际需要发送的数据长度
       *@ret： 返回实际发送的字节数，如果返回-1，则有error发生
      */
    virtual int SendMsg (const char *buf, int len) = 0;
};