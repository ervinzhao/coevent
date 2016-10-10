#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "tcp_service.h"

static int helpSetBlock(int fd, int non_block) {
    int flags;

    /* Set the socket blocking (if non_block is zero) or non-blocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        return -1;
    }

    if (non_block)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}


TcpService::TcpService(EventLoop &evloop)
    : m_evloop(evloop)
{
    m_listening = false;
    m_lastErrorCode = 0;
}

TcpService::~TcpService()
{

}

int TcpService::listen(onConnectProc proc, int port, const char *addr)
{
    int ret;
    if(port < 1 || port > 65535) {
        m_lastErrorCode = -1;
        return -1;
    }

    if(strlen(addr) > 15) {
        m_lastErrorCode = -2;
        return -1;
    }

    if(proc == NULL) {
        m_lastErrorCode = -3;
        return -1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        m_lastErrorCode = errno;
        return -1;
    }
    ret = helpSetBlock(sockfd, 1);
    if(ret < 0) {
        m_lastErrorCode = errno;
        return -1;
    }

    struct sockaddr_in saddr;
    if(addr) {
        ret = inet_pton(AF_INET, addr, &saddr.sin_addr);
        if(ret == -1) {
            m_lastErrorCode = errno;
            return -1;
        } else if(ret == 0) {
            m_lastErrorCode = -4;
            return -1;
        }
    } else {
        saddr.sin_addr.s_addr = INADDR_ANY;
    }
    saddr.sin_port = htons((uint16_t) port);
    saddr.sin_family = AF_INET;

    ret = bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret < 0) {
        m_lastErrorCode = errno;
        return -1;
    }

    ret = ::listen(sockfd, 10);
    if(ret < 0) {
        m_lastErrorCode = errno;
        return -1;
    }

    m_evloop.watchFileEvent(sockfd, true, false, this);
    m_fd = sockfd;
    m_listening = true;
    strncpy(m_addr, addr, sizeof(m_addr));
    m_port = port;
    m_onConnect = proc;
    return 0;
}
