#include "philo.h"

int is_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (philo->dead == 1)
    {
        pthread_mutex_unlock(philo->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philo->dead_lock);
    return (0);
}

int create_threads(t_philo **philos, int count)
{
    pthread_t       monitor_thread;
    pthread_t      *threads;
    int             i;

    // allocate philosopher thread array
    threads = malloc(sizeof(pthread_t) * count);
    if (!threads)
        return (printf("Malloc error\n"), 1);

    // create monitor thread first
    if (pthread_create(&monitor_thread, NULL, monitor, (void *)philos) != 0)
    {
        printf("Failed to create monitor thread\n");
        free(threads);
        return (1);
    }

    // create philosopher threads
    i = 0;
    while (i < count)
    {
        if (pthread_create(&threads[i], NULL, routine, (void *)philos[i]) != 0)
        {
            printf("Failed to create thread %d\n", i);

            // join what has been created before exiting
            while (--i >= 0)
                pthread_join(threads[i], NULL);

            pthread_join(monitor_thread, NULL);
            free(threads);
            return (1);
        }
        i++;
    }

    // wait for monitor thread (stops on death or eaten completion)
    pthread_join(monitor_thread, NULL);

    // after monitor stops: join all philo threads
    i = 0;
    while (i < count)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    free(threads);
    return (0);
}
