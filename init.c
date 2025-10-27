/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 02:43:16 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 19:54:56 by marvin           ###   ########.fr       */
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

void	init_rules_belly(t_rules *rules, char **argv)
{
	rules->philo_count = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		rules->must_eat_count = ft_atol(argv[5]);
	else
		rules->must_eat_count = -1;
	rules->start_time = get_time_in_ms();
}

t_rules	*init_rules(char **argv)
{
	int		i;
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	init_rules_belly(rules, argv);
	rules->fork = malloc(sizeof(pthread_mutex_t) * rules->philo_count);
	if (!rules->fork)
		return (NULL);
	while (i < rules->philo_count)
	{
		pthread_mutex_init(&rules->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	pthread_mutex_init(&rules->sim_lock, NULL);
	return (rules);
}

t_philo	*init_philo(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * rules->philo_count);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < rules->philo_count)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &rules->fork[i];
		philo[i].right_fork = &rules->fork[(i + 1) % rules->philo_count];
		philo[i].rules = rules;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = rules->start_time;
		i++;
	}
	return (philo);
}
