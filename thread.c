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

