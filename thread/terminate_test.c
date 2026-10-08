#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Result{
    char *message;
    int length;
} Result;

void *red_thread ( void *arg )
{
    Result *result = malloc(sizeof(Result));
    sleep(1);
    char *message =  strdup("红色线程执行完毕\n");
    result->message = message;
    result->length = strlen(message);
    printf("红色线程执行完毕，长度为: %d\n", result->length);
    pthread_exit(result);
}

void *blue_thread ( void *arg )
{
    Result *result = malloc(sizeof(Result));
    sleep(1);
    char *message =  strdup("蓝色线程执行完毕\n");
    result->message = message;
    result->length = strlen(message);
    printf("蓝色线程执行完毕，长度为: %d\n", result->length);
    pthread_exit(result);
}

int main ( int argc ,char const *argv[])
    {
    pthread_t tid_red, tid_blue;
    Result *red=NULL;
    Result *blue=NULL;

    pthread_create(&tid_red, NULL, red_thread, NULL);
    pthread_create(&tid_blue, NULL, blue_thread, NULL);

    pthread_join(tid_red, (void**)&red);
    pthread_join(tid_blue, (void**)&blue);

    printf("红色线程返回的消息: %s", red->message);
    printf("蓝色线程返回的消息: %s", blue->message);

 
    free(red->message);
    free(red);
    free(blue->message);
    free(blue);

    return 0;
    }