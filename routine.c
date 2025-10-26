/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:39:39 by marvin            #+#    #+#             */
/*   Updated: 2025/10/26 20:47:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	I multiply by 1000 so the microsecond become milisecond,
	since the input we are given is in milisecond and usleep function
	runs microsecond.
*/

void	sub_routine_thinking(t_philo *philo)
{
	long	time;

	time = get_time_in_ms() - philo->rules->start_time;
	pthread_mutex_lock(&philo->rules->print_lock);
	if (philo->rules->stop_sim == 1)
	{
		pthread_mutex_unlock(&philo->rules->print_lock);
		return ;
	}
	printf("%lo Philosopher %i is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

void	sub_routine_sleeping(t_philo *philo)
{
	long	time;

	time = get_time_in_ms() - philo->rules->start_time;
	pthread_mutex_lock(&philo->rules->print_lock);
	if (philo->rules->stop_sim == 1)
	{
		pthread_mutex_unlock(&philo->rules->print_lock);
		return ;
	}
	printf("%lo Philosopher %i is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	usleep(philo->rules->time_to_sleep * 1000);
}

void	sub_routine_eating(t_philo *philo)
{
	long	time;

	time = get_time_in_ms() - philo->rules->start_time;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->rules->print_lock);
	philo->last_meal_time = get_time_in_ms();
	if (philo->rules->stop_sim == 1)
	{
		pthread_mutex_unlock(&philo->rules->print_lock);
		return ;
	}
	printf("%lo Philosopher %i is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	philo->meals_eaten = philo->meals_eaten + 1;
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->rules->stop_sim == 0)
	{
		sub_routine_eating(philo);
		sub_routine_sleeping(philo);
		sub_routine_thinking(philo);
	}
	return (NULL);
}
