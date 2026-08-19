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
    char *mq_name = "/father_son_mq";//消息队列名称
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);

    if  (mqdes == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    char read_buffer[1024];
    struct timespec ts;

    //不断接受消息队列数据
    while(1){

        memset(read_buffer, 0, sizeof(read_buffer));//清空缓冲区
        //先获取当前时间，设置 5 秒超时，再调用接收
        clock_gettime(0,&ts);
        ts.tv_sec +=15;
        ssize_t bytes_read = mq_timedreceive(mqdes, read_buffer, sizeof(read_buffer), NULL, &ts);//从消息队列中接收数据
        //wrong，出错了报错

        if (bytes_read < 0) {//如果接收失败（含超时）
            perror("read"); 
            continue;
        }
        //停止接受：收到结束标记（1 字节的 EOF）则退出
       if (bytes_read == 1 && (unsigned char)read_buffer[0] == (unsigned char)EOF){
        printf("E0F,exit\n");
        break;
       }

        //打印收到的消息（消费，不回显到队列，否则会自我循环）
        printf("收到消息: %s\n", read_buffer);

    }
    // 不要在这里 mq_unlink 删除队列！
    // 否则若下次先启动 producer（无 consumer 接收），消息会滞留并被"推迟"到下次才收到，
    // 造成"奇数次收到、偶数次收不到"的假象。队列残留可用 rm /dev/mqueue/father_son_mq 手动清理。
    mq_close(mqdes);
    // mq_unlink(mq_name); // 删除消息队列
   return 0;
}