#include <pthread.h>
#include <stdio.h>

int total = 0;
pthread_mutex_t mutex;

void *RedMakeMoney(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        char *name = (char *)arg;
        pthread_mutex_lock(&mutex);
        printf("%s: %d\n", name, total);
        total++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *WhiteMakeMoney(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        char *name = (char *)arg;
        pthread_mutex_lock(&mutex);
        printf("%s: %d\n", name, total);
        total++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main  ( int argc ,char const *argv[])
{
    pthread_t red , white;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&red, NULL, RedMakeMoney, "ROSE");
    pthread_create(&white, NULL, WhiteMakeMoney, "LILY");
    pthread_join(red, NULL);
    pthread_join(white, NULL);
    printf("total = %d\n", total);
    pthread_mutex_destroy(&mutex);
    return 0;
}