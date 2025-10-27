/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:39:39 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 20:14:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		check_for_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->sim_lock);
	if (philo->rules->stop_sim != 0)
	{
		pthread_mutex_unlock(&philo->rules->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->sim_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_for_death(philo) == 1)
			return (NULL);
		sub_routine_eating(philo);
		if (check_for_death(philo) == 1)
			return (NULL);
		sub_routine_sleeping(philo);
		if (check_for_death(philo) == 1)
			return (NULL);
		sub_routine_thinking(philo);
	}
	return (NULL);
}
