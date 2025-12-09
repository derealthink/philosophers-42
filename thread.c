/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:07:12 by uponci            #+#    #+#             */
/*   Updated: 2025/12/09 18:07:14 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	create_threads(t_philo *philos, int count)
{
	pthread_t	monitor_thread;
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * count);
	if (!threads)
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)philos) != 0)
	{
		free(threads);
		return (1);
	}
	i = 0;
	while (i < count)
	{
		if (pthread_create(&threads[i], NULL, routine, (void *)&philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(threads[i], NULL);
			pthread_join(monitor_thread, NULL);
			free(threads);
			return (1);
		}
		i++;
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}
