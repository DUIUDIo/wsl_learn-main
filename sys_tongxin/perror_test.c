#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<errno.h>

int num = 0 ;

int main ( int argc, char const*argv[] )
    {
     pid_t pid = fork();
    if (pid == -1)
        {
            perror("错误，无法创建子进程");
            return -1;  
        }

    if(pid == 0 ){
        num=1;
        printf("子进程中num的值为: %d\n", num);
    }   
    else{
        sleep(1);

        printf("父进程中num的值为: %d\n", num);
    }
        return 0;
    }