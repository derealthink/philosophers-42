#include "philo.h"


int monitor_dead(t_philo *philo, size_t now)
{
    pthread_mutex_lock(philo->meal_lock);
    if ((int)(now - philo->last_meal) >= philo->time_die)
    {
        pthread_mutex_unlock(philo->meal_lock);
        print_message("died", philo->id, philo);
        pthread_mutex_lock(philo->dead_lock);
        *philo->dead_flag = 1;
        pthread_mutex_unlock(philo->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

int monitor_eaten(t_philo *philo)
{
    if (philo->nb_eat == -1)
        return (0);
    pthread_mutex_lock(philo->meal_lock);
    if (philo->eaten >= philo->nb_eat)
    {
        pthread_mutex_unlock(philo->meal_lock);
        pthread_mutex_lock(philo->dead_lock);
        *philo->dead_flag = 1;
        pthread_mutex_unlock(philo->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

void *monitor(void *arg)
{
    t_philo *philo;
    int      i;
    size_t   now;
    int      stop;
    
    philo = (t_philo *)arg;
    now = get_time();
    stop = 0;    
    while (!stop)
    {
        i = 0;
        while (i < philo[0].nb_philo)
        {
            now = get_time();
            if (monitor_dead(&philo[i], now))
            {
                stop = 1;  // Signal to exit outer loop
                break;
            }
            if (monitor_eaten(&philo[i]))
            {
                stop = 1;  // Signal to exit outer loop
                break;
            }
            i++;
        }
        if (!stop)
            usleep(500);  // Only sleep if not stopping
    }
    return (NULL);
}

