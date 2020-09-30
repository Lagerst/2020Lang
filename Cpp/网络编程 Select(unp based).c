#include "unp.h"

int main(int argc, char **argv) {

  int listenfd, connfd, sockfd, i, maxi, maxfd, nready, client[FD_SETSIZE];
  ssize_t n;
  fd_set rset, allset;
  char buf[MAXLINE];
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;

  listenfd = Socket(PF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);

  maxfd = listenfd;
  maxi = -1;
  for (int i = 0; i < FD_SETSIZE; i++) {
    client[i] = -1;
  }
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);

  while (1) {
    rset = allset;
    nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

    if (FD_ISSET(listenfd, &rset)) {
      clilen = sizeof(cliaddr);
      connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
#ifdef NOTDEF
      printf("new client: %s, port %d\n",
             Inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
             ntohs(cliaddr.sin_port));
#endif
      for (i = 0; i < FD_SETSIZE; i++) {
        if (client[i] < 0) {
          client[i] = connfd;
          break;
        }
      }
      if (i == FD_SETSIZE)
        err_quit("too many clients");
      FD_SET(connfd, &allset);
      if (connfd > maxfd) {
        maxfd = connfd;
      }
      if (i > maxi)
        maxi = i;
      int temp;
      if (--nready <= 0)
        continue;
    }

    for (int i = 0; i <= maxi; i++) {
      if ((sockfd = client[i]) < 0) {
        continue;
      }
      if (FD_ISSET(sockfd, &rset)) {
        if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
          Close(sockfd);
          FD_CLR(sockfd, &allset);
          client[i] = -1;
        } else {
          Writen(sockfd, buf, n);
        }
        if (--nready <= 0)
          break;
      }
    }
  }
}