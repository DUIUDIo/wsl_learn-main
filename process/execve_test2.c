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
    // 检查是否提供了命令行参数
    char *name= "ZJ" ;
 
    //
    printf("test2: 执行命令: %s 编号 PID:%d \n", name, getpid());

    char *args[] = {"execve_test", name, NULL}; // 命令行参数数组，最后一个元素必须是NULL
    char *envp[] = {NULL}; // 环境变量数组，最后一个元素必须是NULL
    execve(args[0], args, envp); // 执行指定的程序
    return 0;
}