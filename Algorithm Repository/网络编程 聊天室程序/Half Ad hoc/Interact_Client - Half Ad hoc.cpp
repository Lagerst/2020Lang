#include "unp.h"
#undef max
#undef min
#include <cjson/cJSON.h>
#include <string>
#include <iostream>
#include <map>

using namespace std;

map<string,pair<string,int>> users;

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


void cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen, char * myname,char * buf)
{
    char sendLineBuf[MAXLINE];

	while(fgets(sendLineBuf, MAXLINE, fp) != NULL){
        cJSON *root=cJSON_CreateObject();
        cJSON *item1=cJSON_CreateString("chat");
        cJSON_AddItemToObject(root,"order",item1);
        cJSON *item2=cJSON_CreateString(myname);
        cJSON_AddItemToObject(root,"username",item2);
        cJSON *item3=cJSON_CreateString(buf);
        cJSON_AddItemToObject(root,"sendto",item3);
        cJSON *temp=cJSON_CreateString(sendLineBuf);
        cJSON_AddItemToObject(root,"content",temp);
        cJSON *hashcode=cJSON_CreateString(std::to_string(SDBMHash(sendLineBuf)).c_str());
        cJSON_AddItemToObject(root,"hashcode",hashcode);

        printf("out:%s\n",cJSON_Print(root));
        //printf("%ld\n",sizeof(cJSON_Print(root)));
        cout<<buf<<users[string(buf)].first<<users[string(buf)].second<<endl;
        redirect(std::make_pair(users[string(buf)].first,users[string(buf)].second),cJSON_Print(root));
		//sendto(sockfd, cJSON_Print(root), MAXLINE, 0, pservaddr, servlen);
        cJSON_Delete(root);
	}
}

void login(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen,char *p)
{
    cJSON *root=cJSON_CreateObject();
    cJSON *item1=cJSON_CreateString("login");
    cJSON_AddItemToObject(root,"order",item1);
    cJSON *item2=cJSON_CreateString(p);
    cJSON_AddItemToObject(root,"username",item2);

    printf("out:%s\n",cJSON_Print(root));

	sendto(sockfd, cJSON_Print(root), MAXLINE, 0, pservaddr, servlen);
	sendto(sockfd, cJSON_Print(root), MAXLINE, 0, pservaddr, servlen);
	sendto(sockfd, cJSON_Print(root), MAXLINE, 0, pservaddr, servlen);
    cJSON_Delete(root);
}

void cliread(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen){
    char sendLineBuf[MAXLINE], recvLineBuf[MAXLINE + 1];
	int nrecv;

	while(1){
		nrecv = recvfrom(sockfd, recvLineBuf, MAXLINE, 0, NULL, NULL);// pay attention to the last two NULLs
		recvLineBuf[nrecv] = 0;
        //std::cout<<recvLineBuf<<std::endl;
        if (!strcmp(recvLineBuf,"User do not exist!\n")){
            printf("Error:User not exist!");
            exit(0);
        }else if (!strcmp(recvLineBuf,"ACK")){
            printf("ACK::Message send successfully!\n");
            continue;
        }else if (!strcmp(recvLineBuf,"NAK")){
            printf("NAK::Message corrupted,please send again!\n");
            continue;
        }
		cJSON* root = cJSON_Parse(recvLineBuf);
        cout<<cJSON_Print(root);

        if (root != NULL){

            cJSON* itemOrder = cJSON_GetObjectItem(root, "order");

            if (!strcmp(itemOrder->valuestring,"map")){
                cJSON* itemName = cJSON_GetObjectItem(root, "username");
                cJSON* itemAddr = cJSON_GetObjectItem(root, "address");
                cJSON* itemPort = cJSON_GetObjectItem(root, "port");
                cout<<"adding map\n"<<string(itemName->valuestring)<<string(itemAddr->valuestring)<<atoi(itemPort->valuestring)<<endl;
                users[string(itemName->valuestring)]=make_pair(string(itemAddr->valuestring),atoi(itemPort->valuestring));
                cout<<users[string(itemName->valuestring)].first<<users[string(itemName->valuestring)].second<<endl;
            }else{
                cJSON* itemName = cJSON_GetObjectItem(root, "username");
                cJSON* itemContent = cJSON_GetObjectItem(root, "content");
                printf("Message from %s:\n    %s",itemName->valuestring,itemContent->valuestring);
            }

            cJSON_Delete(root);
        }
	}
}

void process(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen, char * myname){
    char buf[10];

    printf("type in the user you want to chat with:");
    scanf("%s",buf);

    printf("getting address, please wait:");

    {
        cJSON *root=cJSON_CreateObject();
        cJSON *item1=cJSON_CreateString("getmap");
        cJSON_AddItemToObject(root,"order",item1);
        cJSON *item2=cJSON_CreateString(myname);
        cJSON_AddItemToObject(root,"username",item2);
        cJSON *item3=cJSON_CreateString(buf);
        cJSON_AddItemToObject(root,"sendto",item3);
        cJSON *hashcode=cJSON_CreateString(std::to_string(SDBMHash(buf)).c_str());
        cJSON_AddItemToObject(root,"hashcode",hashcode);
        sendto(sockfd, cJSON_Print(root), MAXLINE, 0, pservaddr, servlen);
        cJSON_Delete(root);
    }

    char sendLineBuf[MAXLINE], recvLineBuf[MAXLINE + 1];
	int nrecv;
    while(1){
		nrecv = recvfrom(sockfd, recvLineBuf, MAXLINE, 0, NULL, NULL);// pay attention to the last two NULLs
		recvLineBuf[nrecv] = 0;
        //std::cout<<recvLineBuf<<std::endl;
        if (!strcmp(recvLineBuf,"User do not exist!\n")){
            printf("Error:User not exist!");
            exit(0);
        }else if (!strcmp(recvLineBuf,"ACK")){
            printf("ACK::Message send successfully!\n");
            continue;
        }else if (!strcmp(recvLineBuf,"NAK")){
            printf("NAK::Message corrupted,please send again!\n");
            continue;
        }
		cJSON* root = cJSON_Parse(recvLineBuf);
        cout<<cJSON_Print(root);

        if (root != NULL){

            cJSON* itemOrder = cJSON_GetObjectItem(root, "order");

            if (!strcmp(itemOrder->valuestring,"map")){
                cJSON* itemName = cJSON_GetObjectItem(root, "username");
                cJSON* itemAddr = cJSON_GetObjectItem(root, "address");
                cJSON* itemPort = cJSON_GetObjectItem(root, "port");
                cout<<"adding map\n"<<string(itemName->valuestring)<<string(itemAddr->valuestring)<<atoi(itemPort->valuestring)<<endl;
                users[string(itemName->valuestring)]=make_pair(string(itemAddr->valuestring),atoi(itemPort->valuestring));
                cout<<users[string(itemName->valuestring)].first<<users[string(itemName->valuestring)].second<<endl;
                break;
            }else{
                cJSON* itemName = cJSON_GetObjectItem(root, "username");
                cJSON* itemContent = cJSON_GetObjectItem(root, "content");
                printf("Message from %s:\n    %s",itemName->valuestring,itemContent->valuestring);
            }

            cJSON_Delete(root);
        }
	}

    if (fork()==0)
        cli(stdin, sockfd, pservaddr, servlen, myname,buf);
    else
        cliread(stdin, sockfd, pservaddr, servlen);
}

int
main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    if (argc != 3){
        printf("usage: cli <ServerIPaddress> <username>");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliaddr.sin_port = htons(0); /* force assignment of ephemeral port */
    bind(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

    login(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr),argv[2]);

    process(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr),argv[2]);

    exit(0);
}