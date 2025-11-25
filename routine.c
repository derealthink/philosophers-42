
#include "philo.h"

void    think(t_philo *philo)
{
    printf("%i : is thinking", philo->id);
}

void    sleep(t_philo *philo)
{
    printf("%i : is sleeping", philo->id);
    ft_usleep(philo->time_sleep);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    printf("%i : has taken a fork", philo->id);
    if (philo->nb_philo == 1)
    {
        ft_usleep(philo->time_die);
        pthread_mutex_unlock(philo->r_fork);
    }
    pthread_mutex_lock(philo->l_fork);
    printf("%i : has taken a fork", philo->id);
    pthread_mutex_lock(philo->meal_lock);
    printf("%i : is eating", philo->id);
    philo->eaten++;//is eating bool may be needed here
    philo->last_meal = get_time();
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_eat);
    pthread_mutex_unlock(philo->r_fork);
    phtread_mutex_unlock(philo->l_fork);

}