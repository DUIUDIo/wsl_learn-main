#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>
#include<time.h>
#include <signal.h>
int main (int argc , char const*argv[])
{
    //创建消息队列
    struct mq_attr attr;
    // 设置消息队列属性
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    // 
    attr.mq_curmsgs = 0;
    char *mq_name = "/father_son_mq";
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);

    if  (mqdes == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {
        // 子进程 receive message
        char read_buffer[1024];
        struct timespec ts;

        clock_gettime(0, &ts);
        ts.tv_sec += 1; // 设置超时时间为5秒
        for(size_t i = 0; i < 5; i++) {
            memset(read_buffer, 0, sizeof(read_buffer));
            clock_gettime(0, &ts);
            ts.tv_sec += 5; // 设置超时时间为5秒
           
            if (mq_timedreceive(mqdes, read_buffer, sizeof(read_buffer), NULL, &ts) == -1) {
                perror("mq_timedreceive");
                exit(EXIT_FAILURE);
            }
            printf("子进程接收到消息: %s\n", read_buffer);
        }
    }

    else {
        // 父进程 send message
        char buffer[1024];
        struct timespec ts;

        clock_gettime(0, &ts);
        ts.tv_sec += 1; // 设置超时时间为5秒
        for(size_t i = 0; i < 5; i++) {
        // 发送消息
        memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, sizeof(buffer), "第 %zu 次 from parent", i + 1);
        clock_gettime(0, &ts);
        ts.tv_sec += 5; // 设置超时时间为5秒

        if (mq_timedsend(mqdes, buffer, strlen(buffer) + 1, 0, &ts) == -1) 
        {
            perror("mq_timedsend");
            exit(EXIT_FAILURE);
        }
        printf("父进程发送消息\n");
        sleep(1);
    }
        
        mq_unlink(mq_name);
    }      
        

    mq_close(mqdes);
   return 0;
}