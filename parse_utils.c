
#include  "philo.h"

int is_digit(char *s)
{
	int i;
	int len;

	len = 0;
	while(s[len])
		len++;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i == len)
		return (1);
	return (0);
}

int is_dig_arr(char **s)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (!is_digit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	get_time(void)
{
	struct	timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while((get_time() - start) < ms)
	{
		if (is_dead(philo))
			return (1);
		usleep(500);
	}
	return (0);
}

void	print_message(char *s, int id, t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->print_lock);
	printf("%zu %i : %s\n", get_time(), id, s);
	pthread_mutex_unlock(philo->print_lock);
}

void	print_debug(int id, t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("\n%zu %i has eaten %i\n",get_time(), id, philo->eaten);
	pthread_mutex_unlock(philo->print_lock);
} 

