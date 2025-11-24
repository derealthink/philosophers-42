
#include "philo.h"

void    init(char **argv)
{
    int nb;
    t_philo *philo;
    t_gen   *gen;

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
    gen = malloc(sizeof(t_gen));
    philo = malloc(sizeof(t_philo) * nb);
    init_gen(gen, philo, argv, nb);
}
void    init_gen(t_gen *gen, t_philo *philo, char **argv, int nb)
{
    gen->dead_lock = malloc(sizeof(pthread_mutex_t));
    gen->meal_lock = malloc(sizeof(pthread_mutex_t));
    gen->print_lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(gen->dead_lock, NULL);
    pthread_mutex_init(gen->meal_lock, NULL);
    pthread_mutex_init(gen->print_lock, NULL);
    gen->dead_flag = 0;
    init_loop_philo(philo, gen, argv, nb);
    gen->philo = philo;
}

void    init_forks(t_philo *tmp, t_gen *gen, int nb)
{
    int i;
    pthread_mutex_t *forks;

    i = 0;
    gen->forks = malloc(sizeof(pthread_mutex_t) * nb);
    while (i < nb)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < nb)
    {
        tmp[i].l_fork = &forks[i];
        tmp[i].r_fork = &forks[(i + 1) % nb];
        i++;
    }
}

t_philo    *init_loop_philo(t_philo *tmp, t_gen *gen, char **argv, int nb)
{
    int i;

    i = 0;
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
        tmp[i].print_lock = gen->print_lock;
        tmp[i].dead_lock = gen->dead_lock;
        tmp[i].meal_lock = gen->meal_lock;
        i++;
    }
    init_forks(tmp, gen ,nb);
    return (tmp);
}
