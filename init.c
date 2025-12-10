/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:59:55 by uponci            #+#    #+#             */
/*   Updated: 2025/12/09 15:59:58 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_philo *tmp, t_gen *gen, int nb)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	gen->forks = malloc(sizeof(pthread_mutex_t) * nb);
	forks = gen->forks;
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

void	init_helper(t_philo *p, t_gen *gen, char **argv, int id)
{
	p->id = id;
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p->nb_eat = ft_atoi(argv[5]);
	else
		p->nb_eat = -1;
	p->eaten = 0;
	p->dead = 0;
	p->last_meal = get_time();
	p->print_lock = gen->print_lock;
	p->dead_lock = gen->dead_lock;
	p->meal_lock = gen->meal_lock;
	p->dead_flag = &gen->dead_flag;
}

t_philo	*init_loop_philo(t_philo *tmp, t_gen *gen, char **argv, int nb)
{
	int		i;
	size_t	start;

	start = get_time();
	i = 0;
	while (i < nb)
	{
		tmp[i].nb_philo = nb;
		init_helper(&tmp[i], gen, argv, i);
		tmp[i].start_time = start;
		i++;
	}
	init_forks(tmp, gen, nb);
	return (tmp);
}

void	init_gen(t_gen *gen, t_philo *philo, char **argv, int nb)
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
