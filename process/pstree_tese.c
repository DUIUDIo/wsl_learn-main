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
    //
    char *name ="DUiDui";
    printf("父进程执行命令: %s 保持编号 PID:%d \n", name, getpid());
    //
    pid_t pid = fork();
    if (pid == -1)
        {
        perror("错误，无法创建子进程");
        return -1;
        }
    else if (pid == 0)
        {
        char *newname = "ZJ";
        char *args[] = {"execve_test", newname, NULL}; // 命令行参数数组，最后一个元素必须是NULL
        char *envs[] = {NULL}; // 环境变量数组，最后一个元素必须是NULL
        int res = execve(args[0], args, envs); // 执行指定的程序
        
        if (res == -1)
            {
            perror("错误，无法执行命令");
            return -1;
            }
        }

        else
        {
        printf("父进程%d等待子进程%d结束,子进程PID: %d\n", getpid(), pid, pid);
            //永久挂起，等输入字符后停止
        fgetc(stdin);
    }

return 0;
    }
    

