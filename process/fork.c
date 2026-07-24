#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc, char *argv[] )
    {
    pid_t pid = fork();
    if (pid == -1)
        {
        perror("错误，无法创建子进程");
        return -1;
        }
    else if (pid == 0)
        {
        printf("这是子进程，PID: %d，父进程PID: %d\n", getpid(), getppid());
        }
    else
        {
        printf("这是父进程，PID: %d，子进程PID: %d\n", getpid(), pid);
        }
    return 0;
    } 