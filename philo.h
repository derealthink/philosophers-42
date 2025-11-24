#ifndef PHILO_H
# define PHILO_H


# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef  struct s_gen
{
  int             nb_philo;
  int             time_die;
  int             time_eat;
  int             time_sleep;
  int             nb_eat;
  pthread_mutex_t print_lock;
  pthread_mutex_t *forks;
} t_gen;

typedef struct s_philo 
{
  int       id;
  long      last_eat;
  int       eat_count;
  pthread_t thread_id;
  t_gen     *gen;
}  t_philo;

int is_dig_arr(char **s);
int ft_atoi(char *s);
void    init_gen(t_gen *gen, char **argv);

#endif
