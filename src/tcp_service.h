#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include "event.h"
#include "event_loop.h"

typedef void onConnectProc(int fd);

class TcpService : public EventHandler
{
private:
    EventLoop &m_evloop;
    char m_addr[16];
    int m_port;
    onConnectProc m_onConnect;
    int m_fd;
    int m_listening;
    int m_lastErrorCode;
public:
    TcpService(EventLoop &evloop);
    ~TcpService();
    int listen(onConnectProc proc, int port, const char *addr = NULL);
    const char *lastError();
    void onRead();
};

#endif // TCPSERVICE_H
