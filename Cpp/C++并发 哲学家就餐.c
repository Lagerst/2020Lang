// using the method 3
// the odd number philosopher get the left hand chopstick
// while the even number philosopher get the opposite.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const int num = 5;
sem_t chopsticks[6] = {1, 1, 1, 1, 1, 1};
int phinum[6] = {0, 1, 2, 3, 4, 5};
int record = 0;

int getnext(int p, int offset) { return (p + offset + num - 1) % num + 1; }

struct tm *gettime() {
  time_t t;
  struct tm *lt;
  time(&t);
  lt = localtime(&t);
  return lt;
}

void *philosopher(void *p) {
  do {
    record++;
    int t = *(int *)p;
    struct tm *lt = gettime();
    printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1,
           lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    printf("    philosopher %d is thinking\n", t);
    srand(time(0));
    sleep(rand() % 5 + 1);
    if (t & 1 == 1) {
      int c = getnext(t, -1);
      sem_wait(&chopsticks[c]);
      int d = getnext(t, 0);
      sem_wait(&chopsticks[d]);
      struct tm *lt = gettime();
      printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1,
             lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
      printf("    philosopher %d is eating, using chopsticks %d and %d\n", t,
             getnext(t, -1), t);
      sleep(rand() % 5 + 1);
      lt = gettime();
      printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1,
             lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
      printf("    philosopher %d stops eating, droping chopsticks %d and %d\n",
             t, getnext(t, -1), t);
      sem_post(&chopsticks[d]);
      sem_post(&chopsticks[c]);
    } else {
      int c = getnext(t, 0);
      sem_wait(&chopsticks[c]);
      int d = getnext(t, -1);
      sem_wait(&chopsticks[d]);
      struct tm *lt = gettime();
      printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1,
             lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
      printf("    philosopher %d is eating, using chopsticks %d and %d\n", t,
             t - 1, t);
      sleep(rand() % 5 + 1);
      lt = gettime();
      printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1,
             lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
      printf("    philosopher %d stops eating, droping chopsticks %d and %d\n",
             t, t - 1, t);
      sem_post(&chopsticks[d]);
      sem_post(&chopsticks[c]);
    }
  } while (record <= 30);
}

int main(void) {
  pthread_t tid[6];
  for (int i = 1; i <= 5; i++) {
    sem_init(&chopsticks[i], 0, 1);
  }
  for (int i = 1; i <= num; i++) {
    pthread_create(&tid[i], NULL, philosopher, &phinum[i]);
  }
  pthread_exit(NULL);
  return 0;
}
