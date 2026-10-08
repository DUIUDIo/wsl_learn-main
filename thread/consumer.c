#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int data = 1; 
int has_data = 0;
pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

void *consumer_thread(void *arg)
{

    pthread_mutex_lock(&mutex);
    for (int i = 1; i <= 5; i++)
    {   
    while (has_data == 0)
    {
        //没有数据，等待生产者线程生产数据
        printf("consumer线程等待数据\n");
        pthread_cond_wait(&not_empty, &mutex);
    }

    has_data = 0; //消费数据
    printf("consumer线程获取数据: %d\n", data);
    printf("\n");
    pthread_cond_signal(&not_full); //通知生产者线程可以生产数据
    pthread_mutex_unlock(&mutex);//解锁给生产者用，互斥锁只有一个可用
    }
    return NULL;
}

void *producer_thread(void *arg)
{ 
    for (int i = 1; i <= 5; i++)
    {
    
    pthread_mutex_lock(&mutex);

    while (has_data == 1)
    {
        //数据已满，等待消费者线程消费数据
        printf("producer线程等待数据被消费\n");
        pthread_cond_wait(&not_full, &mutex);
    }
    has_data = 1; //生产数据
    data = i *10 ; 
    printf("producer线程生产数据: %d\n", data);
    pthread_cond_signal(&not_empty); //通知消费者线程有数据可用
    pthread_mutex_unlock(&mutex);//解锁互斥锁
}
    

    return NULL;
}


int main ( int argc ,char const *argv[])
{
    pthread_t consumer_tid, producer_tid;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    pthread_create(&consumer_tid, NULL, consumer_thread, NULL);
    pthread_create(&producer_tid, NULL, producer_thread, NULL);

    pthread_join(consumer_tid, NULL);
    pthread_join(producer_tid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0; 
}