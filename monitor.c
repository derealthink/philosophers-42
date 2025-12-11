/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:34:17 by uponci            #+#    #+#             */
/*   Updated: 2025/12/09 16:34:19 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_dead(t_philo *philo, size_t now)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((int)(now - philo->last_meal) >= philo->time_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		print_message("died", philo->id, philo);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	monitor_eaten(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (philo->nb_eat == -1)
		return (0);
	while (i < philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].eaten >= philo[i].nb_eat)
			count++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	return (count == philo[0].nb_philo);
}
/*if (philo->nb_eat == -1)
		return (0);
	pthread_mutex_lock(philo->meal_lock);
	if (philo->eaten >= philo->nb_eat)
	{
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);*/

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo[0].nb_philo)
		{
			if (monitor_dead(&philo[i], get_time()))
			{
				return (NULL);
			}
			i++;
		}
		if (monitor_eaten(philo))
		{
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead_flag = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (NULL);
		}
		usleep(500);
	}
}
