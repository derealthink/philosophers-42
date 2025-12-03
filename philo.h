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
  int             last_meal;
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

int     is_dig_arr(char **s);
int     ft_atoi(char *s);
int	    ft_usleep(size_t ms);
size_t	get_time(void);
void	  print_message(char *s, int id, t_philo *philo);
int     is_dead(t_philo *philo);
void    *monitor(void *arg);
void    *routine(void *arg);
int     create_threads(t_philo **philos, int count);
void    clean_exit(t_gen *gen, int nb);
void    init_gen(t_gen *gen, t_philo *philo, char **argv, int nb);

#endif
