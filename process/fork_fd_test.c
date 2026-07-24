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
    int fd = open("example.txt", O_RDWR | O_CREAT |  O_APPEND , S_IRUSR | S_IWUSR);
    if (fd == -1)
        {
        perror("错误，无法打开文件");
        exit(EXIT_FAILURE);
        }
    
    char buffer[256];// 用于存储从文件中读取的数据    

    pid_t pid = fork();
   
    if (pid == -1)// 创建子进程失败
        {
        perror("错误，无法创建子进程");
        exit(EXIT_FAILURE);
        }
        
    else if (pid == 0)// 子进程
        {
        strcpy(buffer, "这是子进程写入的内容:son。\n");
        }
    else// 父进程
        {
        sleep(1); // 确保子进程先写入
        wait(NULL); // 等待子进程结束   
        strcpy(buffer, "这是父进程写入的内容：father。\n");
        }
    
    ssize_t bytesWritten = write(fd, buffer, strlen(buffer));
  
    if (bytesWritten == -1)
        {
        perror("错误，无法写入文件");
        exit(EXIT_FAILURE);
        }

    if(pid == 0) // 子进程关闭文件描述符
        {
        printf("子进程写入了 %zd 字节到文件。\n", bytesWritten);
       
        }
    else // 父进程关闭文件描述符
        {
        printf("父进程写入了 %zd 字节到文件。\n", bytesWritten);
       
        }
    
    close(fd);
    return 0;
    }
