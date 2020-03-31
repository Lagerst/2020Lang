#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<sys/ipc.h>

struct msg_st{
	int msg_type;
	char text[1024];
};

int main(){
	pid_t pid=0;
	pid = fork();
	char buff[1024];
	int msgid=msgget((key_t)1234,IPC_CREAT|0666);
	if (msgid==-1){
		printf("create fail\n");
		exit(1);
	}
	if (pid==0){
		strcpy(buff,"Child process");
		struct msg_st data;
		data.msg_type=1;
		strcpy(data.text,buff);
		if (msgsnd(msgid,(void *)&data,1024,0)==-1){
			printf("send fail\n");
			exit(1);
		}
		if (msgrcv(msgid,(void *)&data,1024,2,0)==-1){
                        printf("receive fail\n");
                        exit(1);
                }
		printf("successfully receive message:\n");
		printf(data.text);
	}
	else{
		strcpy(buff,"Father process");
                struct msg_st data;
                data.msg_type=2;
                strcpy(data.text,buff);
                if (msgsnd(msgid,(void *)&data,1024,0)==-1){
	                printf("send fail\n");
                        exit(1);
                }
                if (msgrcv(msgid,(void *)&data,1024,1,0)==-1){
                        printf("receive fail\n");
                        exit(1);
                }
                printf("successfully receive message:\n");
                printf(data.text);
	}
}
