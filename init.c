/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 02:43:16 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 17:25:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
   argv[1] == number_of_philosophers
   argv[2] == time_to_die
   argv[3] == time_to_eat
   argv[4] == time_to_sleep
   argv[5] == number_of_times_each_philosopher_must_eat
*/

static int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&rules->stop_mutex, NULL))
		return (1);
	return (0);
}

int	rules_init(t_rules *rules)
{
	rules->stop = false;
	if (init_mutexes(rules))
		return (1);
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philos)
		return (1);
	return (0);
}

int	philos_init(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philos[i].last_meal_ms = 0;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].rules = rules;
		pthread_mutex_init(&rules->philos[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}
