/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:53:50 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 17:24:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_lock_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);	
	}
}

void	fork_unlock_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);	
	}
}

void	sub_routine_eating(t_philo *philo)
{
	long long	time;
	// long long	last_meal;

	fork_lock_order(philo);
	
	pthread_mutex_lock(&philo->rules->start_lock);
	time = get_time_in_ms() - philo->rules->start_time;
	pthread_mutex_unlock(&philo->rules->start_lock);
	
	pthread_mutex_lock(&philo->rules->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	// last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	
	pthread_mutex_lock(&philo->rules->print_lock);
	// printf("%lld\n", last_meal);
	printf("%lld %i is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	
	pthread_mutex_lock(&philo->rules->meal_eaten_lock);
	philo->meals_eaten = philo->meals_eaten + 1;
	pthread_mutex_unlock(&philo->rules->meal_eaten_lock);
	
	usleep(philo->rules->time_to_eat * 1000);
	
	fork_unlock_order(philo);
}
