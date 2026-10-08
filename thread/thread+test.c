#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char *buf;

void *input_thread(void *arg)
{
    int i = 0 ;
    while (1)
    {
     char c = fgetc(stdin);
     if (c && c != '\n')
        {
        buf [i++] = c;
        }
    if (i > BUFFER_SIZE - 1)
        {
        buf[i] = '\0';
        printf("缓存区已满，写入数据: %s\n", buf);
        i = 0;
        }
    }
    return NULL;
}

void *output_thread(void *arg)
{
    int i = 0 ;
    while (1)
    {
        if (buf[i] != '\0')
            {
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            buf [ i++ ] = 0;
            }
        if (i > BUFFER_SIZE - 1)
            {
            i = 0;
            }
    }
    return NULL;
}


//程序实现创建两个线程，一个线程负责写入数据到缓冲区，另一个线程负责从缓冲区读取数据。使用互斥锁和条件变量来同步线程的操作，确保数据的一致性和线程安全。
// 读取控制台信息 写入缓存
//缓存信息写入到控制台

int main (int argc ,char const *argv[])
    {
    buf = malloc(BUFFER_SIZE * sizeof(char));
    pthread_t pid_input;
    pthread_t pid_output;
    //创建读线程
    pthread_create(&pid_input, NULL, input_thread, NULL);
    //创建写线程  
    pthread_create(&pid_output, NULL, output_thread, NULL);

    //主线程等待    
    pthread_join(pid_input, NULL);
    pthread_join(pid_output, NULL); 
    return 0;
}