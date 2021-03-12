#include "unp.h"
#undef max
#undef min
#include <map>
#include <iostream>
#include <string>
#include <cjson/cJSON.h>

using namespace std;
map<string,pair<string,int>> users;

void process(int sockfd);

unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;

    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

int
main(int argc, char **argv)
{
    int listenfd, connfd, sockfd, nready, maxfdp1, pid;
    char mesg[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
    void sig_chld(int);

        /* 4create listening TCP socket */
        //listenfd = Socket(AF_INET, SOCK_STREAM, 0);
        //bzero(&servaddr, sizeof(servaddr));
        //servaddr.sin_family = AF_INET;
        //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        //servaddr.sin_port = htons(SERV_PORT);
        //Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        //Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
        //Listen(listenfd, LISTENQ);


    /* 4create UDP socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
    /* end udpservselect01 */

    process(sockfd);
}

pair<string,int> LoginUser(string s,string ip,int port){

    cJSON* root = cJSON_Parse(s.c_str());

    if (root == NULL)
    {
        cJSON_Delete(root);
        return make_pair(string("123"),-1);
    }

    cJSON* itemContent = cJSON_GetObjectItem(root, "content");
    cJSON *hashcode = cJSON_GetObjectItem(root, "hashcode");

    if (itemContent!=nullptr && hashcode!=nullptr && SDBMHash(itemContent->valuestring)!=atoi(hashcode->valuestring)){
        return make_pair(string("123"),-2);//corrupted
    }

    cJSON* itemOrder = cJSON_GetObjectItem(root, "order");
    cJSON* itemName = cJSON_GetObjectItem(root, "username");
    cJSON* itemSendto = cJSON_GetObjectItem(root, "sendto");

    users[itemName->valuestring]=std::make_pair(ip,port);

    if (!strcmp(itemOrder->valuestring,"login")){
        std::cout<<"Login successful:["<<ip<<":"<<port<<"]"<<itemName->valuestring;
        cJSON_Delete(root);
        return make_pair(string("123"),0);//Login
    }

    if (users.find(itemSendto->valuestring)==users.end()){
        cJSON_Delete(root);
        return make_pair(string("123"),-1);//user not exist
    }

    string temp=string(itemSendto->valuestring);
    cJSON_Delete(root);
    return users[temp];//return user information
}

void writ(pair<string,int> target,string buf, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen){

	sendto(sockfd, buf.c_str(), MAXLINE, 0, pservaddr, servlen);

}

void redirect(pair<string,int> target,string buff){
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(target.second);
    inet_pton(AF_INET, target.first.c_str(), &servaddr.sin_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliaddr.sin_port = htons(0); /* force assignment of ephemeral port */
    bind(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

    writ(target, buff, sockfd, (SA *) &servaddr, sizeof(servaddr));

}

void process(int sockfd){
    printf("Server Start at Port:%d\n",SERV_PORT);
    while(1){
        char buff[1024]={0};
        SA * local;
        ssize_t s;
        socklen_t len;
        //接收数据（描述符，放到哪，内存大小，阻塞，从哪来，数据大小）
        s = recvfrom(sockfd,buff,1023,0,(struct sockaddr*)&local,&len);
        struct sockaddr_in *sock = ( struct sockaddr_in*)&local;
        int port = ntohs(sock->sin_port);
        #ifdef __MINGW32__  //windows上打印方式
            printf("ip:port  %s : %d",inet_ntoa(sock->sin_addr),port);
        #else              //linux上打印方式
            struct in_addr in  = sock->sin_addr;
            char str[INET_ADDRSTRLEN];   //INET_ADDRSTRLEN这个宏系统默认定义 16
            //成功的话此时IP地址保存在str字符串中。
            inet_ntop(AF_INET,&in, str, sizeof(str));
        #endif
        printf("Server Receive Message from ip:port  %s : %d:\n      %s",str,port,buff);
        pair<string,int> target;
        target=LoginUser(buff,str,port);
        if (target.second==-1){
            printf("User do not exist!\n");
            redirect(std::make_pair(str,port),"User do not exist!\n");//redirect message to sender
            continue;
        }else if (target.second==0){
            continue;
        }else if (target.second==-2){
            redirect(std::make_pair(str,port),"NAK");
            continue;
        }
        redirect(std::make_pair(str,port),"ACK");
        cout<<"redirecting\n";
        redirect(target,buff);//redirect message to receiver
    }
}