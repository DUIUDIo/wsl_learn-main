#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
  int pipefd[2];
  pid_t pid;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // 第一步：创建管道（必须在 fork 之前）
  if (pipe(pipefd) == -1)
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // 第二步：创建子进程
  pid = fork();
  if (pid == -1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    // ===== 子进程：从管道读数据 =====
    close(pipefd[1]);  // 关闭不需要的写端

    printf("[子进程] 接收到数据: ");
    char buf;
    while (read(pipefd[0], &buf, 1) > 0)
    {
      write(STDOUT_FILENO, &buf, 1);
    }
    write(STDOUT_FILENO, "\n", 1);

    close(pipefd[0]);  // 关闭读端
    exit(EXIT_SUCCESS);
  }
  else
  {
    // ===== 父进程：向管道写数据 =====
    close(pipefd[0]);  // 关闭不需要的读端

    printf("[父进程 %d] 发送数据: %s\n", getpid(), argv[1]);
    write(pipefd[1], argv[1], strlen(argv[1]));

    close(pipefd[1]);  // 关闭写端（读端会收到 EOF）
    waitpid(pid, NULL, 0);
    exit(EXIT_SUCCESS);
  }
}