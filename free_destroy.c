#include "philo.h"

void destroy_mutexes(t_gen *gen, int nb)
{
    int i;

    if (!gen)
        return;

    // Destroy global mutexes
    if (gen->dead_lock)
        pthread_mutex_destroy(gen->dead_lock);
    if (gen->meal_lock)
        pthread_mutex_destroy(gen->meal_lock);
    if (gen->print_lock)
        pthread_mutex_destroy(gen->print_lock);

    // Destroy fork mutexes
    if (gen->forks)
    {
        i = 0;
        while (i < nb)
        {
            pthread_mutex_destroy(&gen->forks[i]);
            i++;
        }
    }
}

void free_all(t_gen *gen)
{
    if (!gen)
        return;
    
    // free fork array
    if (gen->forks)
        free(gen->forks);

    // free global mutex pointers
    if (gen->dead_lock)
        free(gen->dead_lock);
    if (gen->meal_lock)
        free(gen->meal_lock);
    if (gen->print_lock)
        free(gen->print_lock);

    // free philosophers array
    if (gen->philo)
        free(gen->philo);

    // free gen itself
    free(gen);
}

void clean_exit(t_gen *gen, int nb)
{
    destroy_mutexes(gen, nb);
    free_all(gen);
}
