/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:39:39 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 17:22:20 by marvin           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->rules->meal_lock);
	pthread_mutex_lock(&philo->rules->start_lock);
	philo->rules->start_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->rules->start_lock);
	philo->last_meal_time = philo->rules->start_time;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		sub_routine_eating(philo);
		if (check_for_death(philo) == 1)
			return (NULL);
		sub_routine_sleeping(philo);
		if (check_for_death(philo) == 1)
			return (NULL);
		sub_routine_thinking(philo);
		if (check_for_death(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
