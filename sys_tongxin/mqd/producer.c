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
    char write_buffer[1024];
    struct timespec ts;

    //不断发送消息队列数据
    while(1){


        memset(write_buffer, 0, sizeof(write_buffer));
//读取？
        ssize_t bytes_read = read(STDIN_FILENO, write_buffer, sizeof(write_buffer));
        clock_gettime(0,&ts);
        ts.tv_sec +=15;
        //read 出错（注意：返回 0 表示 EOF，不是错误）
        if (bytes_read < 0) {
            perror("read");
            continue;
        }
        //EOF：发送结束标记并退出
       if (bytes_read == 0){
        printf("E0F,exit\n");
        char eof = EOF;
        if( mq_timedsend(mqdes,&eof,1,0,&ts) == -1){
            perror("mq_timedsend");
        }
        break;
       }
//
       if( mq_timedsend( mqdes, write_buffer , strlen(write_buffer) , 0 , &ts) == -1){
        perror("mq_timedsend");
       }

    }
   
    mq_close(mqdes);
   return 0;
}