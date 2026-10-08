#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *arg)
{
   while (1)
   {
    printf("子线程正在运行\n");
    sleep(1);
    /* code */
   }
   
}

int main ( int argc , char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);
    sleep(5);
    printf("请求取消子线程\n");
    pthread_cancel(tid);
    pthread_join(tid, NULL);
    printf("主线程执行完毕,cancel\n");
    return 0;
}