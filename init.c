
#include "philo.h"

void    init_philo(char **argv)
{
    int nb;

    t_philo *philo;
    if (!is_dig_arr(argv))
        {
            printf("parse error\n");
            return ;
        }
    nb = ft_atoi(argv[1]);
    if (nb <= 0)
    {
        printf("insufficient n  of philosophers\n");
        return ;
    }
    init_loop_philo(philo, argv, nb);
}
t_philo    *init_loop_philo(t_philo *tmp, char **argv, int nb)
{
    int i;

    i = 0;
    tmp = malloc(sizeof(t_philo) * nb);
    while (i < nb)
    {
        tmp[i].id = i;
        tmp[i].nb_philo = nb;
        tmp[i].time_die = ft_atoi(argv[2]);
        tmp[i].time_eat = ft_atoi(argv[3]);
        tmp[i].time_sleep = ft_atoi(argv[4]);
        if (argv[5])
            tmp[i].nb_eat = ft_atoi(argv[5]);
        else
            tmp[i].nb_eat = -1;
        tmp[i].eaten = 0;
        tmp[i].dead = 0;
        pthread_mutex_init(&print_lock, NULL);
        pthread_mutex_init(&dead_lock, NULL);
        pthread_mutex_init(&meal_lock, NULL);
        pthread_mutex_init(&r_fork, NULL);
        pthread_mutex_init(&l_fork, NULL);
        i++;
    }
    return (tmp);
}
