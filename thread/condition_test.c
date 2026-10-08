#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int has_letter = 0 ; 

void *read_thread ( void *arg )
{
    char letter = (char)arg;
    pthread_mutex_lock(&mutex);// 加锁互斥锁，保护共享变量 has_letter
    
    while ( has_letter == 0 )
    {
        printf("read线程等待条件变量\n");
        pthread_cond_wait(&cond, &mutex);
    }
    printf("read线程收到通知，has_letter=%d，letter=%c\n", has_letter, letter);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main ( int argc ,char const *argv[])
{
    pthread_t pid_input,pid_input2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&pid_input, NULL, read_thread, 'A');
    pthread_create(&pid_input2, NULL, read_thread, 'B');
    sleep(1);

    pthread_mutex_lock(&mutex);// 加锁互斥锁，保护共享变量 has_letter
    has_letter = 1;
    printf("main线程发送通知\n");    
    pthread_cond_broadcast(&cond);// 发送条件变量通知，唤醒等待的线程
    pthread_mutex_unlock(&mutex);

    pthread_join(pid_input, NULL);
    pthread_join(pid_input2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}