#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *thread_function(void *arg)
{

    printf("子线程正在运行\n");
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    
    for ( int i = 0 ; i<=5 ; i++){
        printf("任务正在运行,i=%d\n",i);
        sleep(1);
        }
    printf("子线程取消状态已恢复\n");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    
    while (1)
    {
        printf("普通线程正在运行\n");
        sleep(1);
    }
   return NULL;

}
int main ( int argc , char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);
    sleep(1);
    printf("请求取消子线程\n");
    pthread_cancel(tid);
    pthread_join(tid, NULL);
    printf("主线程执行完毕,cancel\n");
    return 0;
}
