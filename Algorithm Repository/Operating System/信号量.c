#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

const int num_consumer=4,num_producer=3,num_buffer=5;
sem_t empty,full,mutex;
int queue[1000+1]={0};
_Bool flag=1;
int ql=0,qr=0,list[6]={0,1,2,3,4,5};
FILE* Filename; 

static inline int getnext(){
	int temp;
	if (fscanf(Filename,"%d",&temp)==EOF){ 
		flag=0;
		return -1;
	}
	return temp;
}

static inline int next(int i){
	if (i+1==num_buffer)
		return 0;
	return i+1;
}

static inline struct tm* gettime(){
        time_t t;
        struct tm * lt;
        time (&t);
        lt = localtime(&t);
        return lt;
}

void* consumer(void* p){
	int isfull;
	while(flag||isfull>0){
		sleep(rand()%5+1);
		sem_wait(&full);
		sem_wait(&mutex);
		struct tm *lt=gettime();
		printf ("%d/%d/%d %d:%d:%d\n",lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,lt->tm_hour,lt->tm_min,lt->tm_sec);
		printf("    Consumer %d:",*(int*)p);
		printf("    read queue[%d]=%d\n",ql,queue[ql]);
		ql=next(ql);
		sem_post(&mutex);
		sem_post(&empty);
		sem_getvalue(&full,&isfull);
	}
}

void* producer(void* p){
	while (flag){
		sleep(rand()%3+1);
		sem_wait(&empty);
		sem_wait(&mutex);
		struct tm *lt=gettime();
		printf ("%d/%d/%d %d:%d:%d\n",lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,lt->tm_hour,lt->tm_min,lt->tm_sec);
		printf("    Producer %d:",*(int*)p);
                int temp=getnext();
		if (temp!=-1){
			queue[qr]=temp;
			printf("    write %d to queue[%d]\n",temp,qr);
                	qr=next(qr);
                	sem_post(&mutex);
                	sem_post(&full);
		}else{
			printf("    No data to produce now, Stop producing!\n");
			sem_post(&mutex);
			sem_post(&empty);
		}
	}
}

int main(void)
{
	pthread_t tid[10];
	sem_init(&empty,0,num_buffer);
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);
	srand(time(0));
	Filename=fopen("Data","r+");
        for (int i=1;i<=num_consumer;i++) {
		pthread_create(&tid[i],NULL,consumer,&list[i]);
	}
	for (int i=1;i<=num_producer;i++) {
		pthread_create(&tid[i+num_consumer],NULL,producer,&list[i]);
	}
	pthread_exit(NULL);
	return 0;
}

