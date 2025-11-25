#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef  struct s_philo
{
  int             id;
  int             nb_philo;
  int             time_die;
  int             time_eat;
  int             time_sleep;
  int             nb_eat;
  int             eaten;
  int             dead;
  pthread_mutex_t *print_lock;
  pthread_mutex_t *dead_lock;
  pthread_mutex_t *meal_lock;
  pthread_mutex_t *r_fork;
  pthread_mutex_t *l_fork;
} t_philo;

typedef struct s_gen 
{
  pthread_mutex_t *dead_lock;
  pthread_mutex_t *meal_lock;
  pthread_mutex_t *print_lock;
  pthread_mutex_t *forks;
  int              dead_flag;
  t_philo     *philo;
}  t_gen;

int is_dig_arr(char **s);
int ft_atoi(char *s);

#endif
