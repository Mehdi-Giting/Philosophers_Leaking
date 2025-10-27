/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:07:28 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 19:55:09 by marvin           ###   ########.fr       */
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
	free(philo);
	free(rules);
}
