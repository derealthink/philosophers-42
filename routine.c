
#include "philo.h"

void    think(t_philo *philo)
{
    print_message("is thinking", philo->id, philo);
}

void    ph_sleep(t_philo *philo)
{
    print_message("is sleeping", philo->id, philo);
    ft_usleep(philo->time_sleep);
}

void   eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_message("has taken a fork", philo->id, philo);
    if (philo->nb_philo == 1)
    {
        ft_usleep(philo->time_die);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);
    print_message("has taken a fork", philo->id, philo);
    pthread_mutex_lock(philo->meal_lock);
    print_message("is eating", philo->id, philo);
    philo->eaten++;//is eating bool may be needed here
    philo->last_meal = get_time();
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_eat);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void    *routine(void *arg)
{
    eat(arg);
    think(arg);
    ph_sleep(arg);

}

void *monitor(void *arg)
{
    t_philo **philo;
    int      i;
    size_t   now;
    philo = (t_philo **)arg;
    while (1)
    {
        i = 0;
        while (i < philo[0]->nb_philo)
        {
            now = get_time();
            if (monitor_dead(philo[i], now))
                return (NULL);
            if (monitor_eaten(philo[i]))
                return (NULL);
            i++;
        }
        usleep(500);
    }
}

int monitor_dead(t_philo *philo, size_t now)
{
    pthread_mutex_lock(philo->meal_lock);
    if ((int)(now - philo->last_meal) >= philo->time_die)
    {
        pthread_mutex_unlock(philo->meal_lock);
        pthread_mutex_lock(philo->dead_lock);
        philo->dead = 1;
        pthread_mutex_unlock(philo->dead_lock);
        print_message("died", philo->id, philo);
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
        philo->dead = 1;
        pthread_mutex_unlock(philo->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

