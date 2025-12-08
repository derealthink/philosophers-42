
#include "philo.h"

void    think(t_philo *philo)
{
    print_message("is thinking", philo->id, philo);
}

void    ph_sleep(t_philo *philo)
{
    print_message("is sleeping", philo->id, philo);
    ft_usleep(philo->time_sleep, philo);
}

void   eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_message("has taken a fork", philo->id, philo);
    if (philo->nb_philo == 1)
    {
        ft_usleep(philo->time_die, philo);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);
    print_message("has taken a fork", philo->id, philo);
    pthread_mutex_lock(philo->meal_lock);
    print_message("is eating", philo->id, philo);
    philo->eaten++;
    philo->last_meal = get_time();
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_eat, philo);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->time_eat / 2, philo);
    while(!is_dead(philo))
    {
        eat(arg);
        think(arg);
        ph_sleep(arg);
    }
    return (NULL);
}
