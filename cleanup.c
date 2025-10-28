/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:07:28 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 04:01:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_forks(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_count)
	{
		pthread_mutex_destroy(&rules->fork[i]);
		i++;
	}
	free(rules->fork);
	rules->fork = NULL;
}

void	cleanup_all(t_philo *philo, t_rules *rules)
{
	clean_forks(rules);
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->meal_lock);
	pthread_mutex_destroy(&rules->sim_lock);
	pthread_mutex_destroy(&rules->meal_eaten_lock);
	pthread_mutex_destroy(&rules->start_lock);
	free(philo);
	free(rules);
}
