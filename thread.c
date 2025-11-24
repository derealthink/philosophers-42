#include "philo.h"

void    *test()
{
    printf("thread 1, works");
    return NULL;
}

int main(void)
{
    pthread_t  thread_one = 0 ;

    pthread_create(&thread_one, NULL, test, NULL);

    pthread_join(thread_one, NULL);
}