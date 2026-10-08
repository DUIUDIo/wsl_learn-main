#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct task_data
    {
    int start;
    int end;
    int result;
    };



void *sum_1(void *arg)
{
    struct task_data *data = (struct task_data *)arg;
    int sum = 0;
    for (int i = data->start; i <= data->end; i++)
        {
        sum += i;
        }
    data->result = sum;
    printf("线程计算的和为: %d \n", sum);
    return NULL;
}


int main ( int argc ,char const *argv[])
    {
   
    pthread_t tid1,tid2;
    struct task_data data1 = {1, 50, 0};
    struct task_data data2 = {51, 100, 0};
  
    //创建线程1
    pthread_create(&tid1, NULL, sum_1, &data1);
    //创建线程2
    pthread_create(&tid2, NULL, sum_1, &data2);

   
    //等待线程1结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("两个线程计算的和为: %d \n", data1.result + data2.result);

    return 0;
    }
