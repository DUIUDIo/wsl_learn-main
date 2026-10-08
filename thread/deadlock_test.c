#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t key_lock;
pthread_mutex_t value_lock;


void *White ( void *arg )
{
    pthread_mutex_lock(&key_lock);
    printf("白色线程获取了key锁\n");
    sleep(1);
    if( pthread_mutex_trylock(&value_lock) == 0 )
    {
        printf("白色线程获取了value锁\n");
        pthread_mutex_unlock(&value_lock);
    }
    else
    {
        printf("白色线程获取value锁失败，发生死锁\n");
    }
    pthread_mutex_unlock(&key_lock);
    return NULL;
}

void *Red ( void *arg )
{
    pthread_mutex_lock(&value_lock);
    printf("红色线程获取了value锁\n");
    sleep(1);
    if( pthread_mutex_trylock(&key_lock) == 0 )
    {
        printf("红色线程获取了key锁\n");
        pthread_mutex_unlock(&key_lock);
    }
    else
    {
        printf("红色线程获取key锁失败，发生死锁\n");
    }
    pthread_mutex_unlock(&value_lock);
    return NULL;
}




int main( int argc ,char const *argv[])
{
    pthread_mutex_init(&key_lock, NULL);
    pthread_mutex_init(&value_lock, NULL);
    pthread_t white_thread, red_thread;
    pthread_create(&white_thread, NULL, White, NULL);
    pthread_create(&red_thread, NULL, Red, NULL);
    pthread_join(white_thread, NULL);
    pthread_join(red_thread, NULL);
    pthread_mutex_destroy(&key_lock);
    pthread_mutex_destroy(&value_lock);
    return 0;
}