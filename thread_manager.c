/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:14:34 by marvin            #+#    #+#             */
/*   Updated: 2025/10/26 23:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_creation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
}

void	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	death_check(t_philo *philo)
{
	long	time;

	time = get_time_in_ms() - philo->rules->start_time;
	if ((get_time_in_ms() - philo->last_meal_time) > philo->rules->time_to_die)
	{
		pthread_mutex_lock(&philo->rules->print_lock);
		printf("%ld Philosopher %i has died.\n", time, philo->id);
		pthread_mutex_unlock(&philo->rules->print_lock);
		philo->rules->stop_sim = 1;
		return (0);
	}
	return (1);
}

int	all_meals_eaten_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count
		&& philo[i].meals_eaten >= philo->rules->must_eat_count)
		i++;
	if (i == philo->rules->philo_count)
	{
		pthread_mutex_lock(&philo->rules->print_lock);
		printf("All meals have been eaten.\n");
		pthread_mutex_unlock(&philo->rules->print_lock);
		philo->rules->stop_sim = 1;
		return (0);
	}
	return (1);
}

void	*thread_monitor(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->rules->stop_sim == 0)
	{
		i = 0;
		while (i < philo->rules->philo_count)
		{
			if (death_check(&philo[i]) == 0)
				break ;
			else if (philo->rules->must_eat_count != -1
				&& all_meals_eaten_check(philo) == 0)
				break ;
			else
				i++;
		}
		usleep(1000);
	}
	return (NULL);
}
