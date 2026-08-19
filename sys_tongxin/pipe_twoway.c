#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,const char* argv[])
{
  int pipefd[2];
  pid_t pid;

  if (argc < 2)
  {
    fprintf(stderr, "用法: %s <参数>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  pipe(pipefd);
  pid = fork();

  if(pid == -1){
    perror("failure:\n");
    exit(EXIT_FAILURE);
  }
  else if (pid == 0 ){
    close(pipefd[1]);
    char buf;
    while ( read (pipefd[0], &buf,1)>0){
     write(STDOUT_FILENO,&buf,1);
    }
    write(STDOUT_FILENO,"\n",1);
    exit(EXIT_SUCCESS);
  }
  
  else{
    close(pipefd[0]);
    printf("[父进程 %d] 发送: %s\n", getpid(), argv[1]);
    write(pipefd[1], argv[1], strlen(argv[1]));
    close(pipefd[1]);  // 关闭写端（读端会收到 EOF）
    waitpid(pid, NULL, 0);
    exit(EXIT_SUCCESS);
  }



  return 0;
}
