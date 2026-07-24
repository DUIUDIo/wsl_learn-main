#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char const*argv[] )
    {
    if (argc < 2)
        {
        printf("参数不足，请提供要执行的命令。\n");
        return -1;
        }

    printf("test1: 子进程执行命令: %s 编号 PID:%d \n", argv[1], getpid());
    wait(NULL); // 等待子进程结束
    return 0;
    }