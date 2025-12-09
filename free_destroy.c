/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:57:59 by uponci            #+#    #+#             */
/*   Updated: 2025/12/09 15:58:01 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_gen *gen, int nb)
{
	int	i;

	if (!gen)
		return ;
	if (gen->dead_lock)
		pthread_mutex_destroy(gen->dead_lock);
	if (gen->meal_lock)
		pthread_mutex_destroy(gen->meal_lock);
	if (gen->print_lock)
		pthread_mutex_destroy(gen->print_lock);
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

void	free_all(t_gen *gen)
{
	if (!gen)
		return ;
	if (gen->forks)
		free(gen->forks);
	if (gen->dead_lock)
		free(gen->dead_lock);
	if (gen->meal_lock)
		free(gen->meal_lock);
	if (gen->print_lock)
		free(gen->print_lock);
	if (gen->philo)
		free(gen->philo);
	free(gen);
}

void	clean_exit(t_gen *gen, int nb)
{
	destroy_mutexes(gen, nb);
	free_all(gen);
}
