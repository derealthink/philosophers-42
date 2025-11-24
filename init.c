
#include "philo.h"

void    init_gen(t_gen *gen, char **argv)
{
    if (!is_dig_arr(argv))
        {
            printf("parse error");
            return ;
        }
    gen->nb_philo = ft_atoi(argv[1]);
    if (gen->nb_philo <= 0)
    {
        printf("parse error");
        return ;
    }
    gen->time_die = ft_atoi(argv[2]);
    gen->time_eat = ft_atoi(argv[3]);
    gen->time_sleep = ft_atoi(argv[4]);
    if (argv[5])
        gen->nb_eat = ft_atoi(argv[5]);
    else
        gen->nb_eat = -1;
    gen_forks(gen);
}

void    gen_forks(t_gen *gen)
{
    int i;

    i = 0;
    if (gen->nb_philo)
    {
        gen->forks = malloc(sizeof(pthread_mutex_t) * gen->nb_philo);
        while (i < gen->nb_philo)
        {
            pthread_mutex_init(&gen->forks[i], NULL);  //study
            i++;
        }
    }
}


