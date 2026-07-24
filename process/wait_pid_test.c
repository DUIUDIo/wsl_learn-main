#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char *argv[] )
    {
    int sub_status;
    printf("xiaoduidui\n");

    pid_t pid = fork();
    if (pid == -1)
        {   
            perror("错误，无法创建子进程");
            return -1;
        }
    else if (pid == 0)
        {
            char *args[] = {"/usr/bin/ping", "-c", "5", "www.google.com", NULL}; // 命令行参数数组，最后一个元素必须是NULL
            char *envs[] = {NULL};
            printf("子进程执行 ping 10次 \n");
             printf("这是子进程，PID: %d，父进程PID: %d\n", getpid(), getppid());
            execve(args[0], args, envs); // 执行指定的程序
           
        }
    else
        {
            printf("父进程PID: %d，等待子进程结束，PID: %d   \n", getpid(), pid);
            waitpid(pid, &sub_status , 0); // 等待子进程结束
        }   
    printf("子进程结束，退出状态: %d\n", WEXITSTATUS(sub_status));
    return 0;
    }