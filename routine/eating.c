/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:53:50 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 18:23:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_lock_order(t_philo *philo)
{
	if (philo->id % 2 == 1)
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

void	sub_routine_eating(t_philo *philo)
{
	long	time;

	fork_lock_order(philo);
	time = get_time_in_ms() - philo->rules->start_time;
	philo->last_meal_time = get_time_in_ms();
	if (philo->rules->stop_sim == 1)
		return ;
	pthread_mutex_lock(&philo->rules->print_lock);
	printf("%lo Philosopher %i is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	philo->meals_eaten = philo->meals_eaten + 1;
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
