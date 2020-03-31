#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h> /* ISO C variable aruments */
#include <arpa/inet.h>

#define ssize_t long

#define MAXLINE 1024
#define LISTENQ 1024

#define SA struct sockaddr

int main(int argc,char *argv[]){
    if (argc!=2){
        printf("Usage:/prog <port>");
        exit(-1);
    }
    int listenfd,Result=0;
    struct sockaddr_in cliaddr, servaddr;

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(/*SERV_PORT*/atoi(argv[1]));
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    int iEpollFd = epoll_create(1024);

    struct epoll_event oEvent;
    memset(&oEvent, 0, sizeof(oEvent));
    oEvent.events = EPOLLIN;
    oEvent.data.fd = listenfd;

    Result=epoll_ctl(iEpollFd, EPOLL_CTL_ADD, listenfd, &oEvent);

    struct epoll_event aoEvents[1024];
    uint8_t acRecvBuf[1024 * 1024];

    while (1)
    {
        printf("Start epoll_wait\n");
        int iFdCnt = epoll_wait(iEpollFd, aoEvents, 1024, -1);
        printf("Recv events: %d\n",iFdCnt);

        for (int i = 0; i < iFdCnt; i++)
        {
            if (aoEvents[i].data.fd == listenfd)
            {
                struct sockaddr_in oClientAddr;
                socklen_t iAddrLen = sizeof(oClientAddr);
                int iAcceptFd = accept(listenfd, (struct sockaddr *)&oClientAddr, &iAddrLen);

                printf("recv connection from %s:%d\n",inet_ntoa(oClientAddr.sin_addr),ntohs(oClientAddr.sin_port));

                oEvent.events = EPOLLIN;
                oEvent.data.fd = iAcceptFd;
                epoll_ctl(iEpollFd, EPOLL_CTL_ADD, iAcceptFd, &oEvent);
            }
            else
            {
                int iCurFd = aoEvents[i].data.fd;
                ssize_t iRecvLen = recv(iCurFd, acRecvBuf, sizeof(acRecvBuf), 0);
                if (iRecvLen < 0)
                {
                    printf("fail to recv, close connection, err: %s\n", strerror(errno));
                    if (epoll_ctl(iEpollFd, EPOLL_CTL_DEL, iCurFd, NULL) < 0)
                    {
                        printf("fail to del fd from epoll, err: %s\n", strerror(errno));
                    }
                    close(iCurFd);
                    continue;
                }
                if (iRecvLen == 0)
                {
                    printf( "connection closed by client: %s\n" , strerror(errno));
                    if (epoll_ctl(iEpollFd, EPOLL_CTL_DEL, iCurFd, NULL) < 0)
                    {
                        printf("fail to del fd from epoll, err: %s\n", strerror(errno));
                    }
                    close(iCurFd);
                    continue;
                }
                printf("recv data len: %ld\n",iRecvLen);

                ssize_t iSendLen = send(iCurFd, acRecvBuf, iRecvLen, 0);
                if (iSendLen < 0)
                {
                    //cerr << "fail to send, err: " << strerror(errno) << endl;
                    if (epoll_ctl(iEpollFd, EPOLL_CTL_DEL, iCurFd, NULL) < 0)
                    {
                        //cerr << "fail to del fd from epoll, err: " << strerror(errno) << endl;
                    }
                    close(iCurFd);
                    break;
                }
                printf("echo to client, len: %ld ,content: %s",iSendLen,acRecvBuf);
            }
        }
    }

}