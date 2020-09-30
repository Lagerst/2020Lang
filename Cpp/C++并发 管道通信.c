#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  pid_t pid;
  // the process 1
  if (pipe(fd) == -1) {
    printf("pipe error!\n");
    exit(1);
  }
  pid = fork();
  if (pid == 0) {
    char buff[1024] = "Child process 1 is sending a message!\n";
    close(fd[0]);
    if (write(fd[1], buff, 1024) == -1) {
      printf("writing error!\n");
      exit(1);
    } else {
      printf("Process 1 Successfully writing!\n");
    }
    close(fd[1]);
    exit(0);
  } else {
    int status;
    waitpid(pid, &status, 0);
    char buff[1024];
    memset(buff, 0, 1024);
    close(fd[1]);
    if (read(fd[0], buff, 1024) == -1) {
      printf("reading error!\n");
      exit(1);
    }
    printf("Successfully receive message:\n");
    printf("%s", buff);
  }
  // process 2
  if (pipe(fd) == -1) {
    printf("pipe error!\n");
    exit(1);
  }
  pid = fork();
  if (pid == 0) {
    char buff[1024] = "Child process 2 is sending a message!\n";
    close(fd[0]);
    if (write(fd[1], buff, 1024) == -1) {
      printf("writing error!\n");
      exit(1);
    } else {
      printf("Process 2 Successfully writing!\n");
    }
    close(fd[1]);
    exit(0);
  } else {
    int status;
    waitpid(pid, &status, 0);
    char buff[1024];
    memset(buff, 0, 1024);
    close(fd[1]);
    if (read(fd[0], buff, 1024) == -1) {
      printf("reading error!\n");
      exit(1);
    }
    close(fd[0]);
    printf("Successfully receive message:\n");
    printf("%s", buff);
  }
}
