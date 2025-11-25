
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
    
}