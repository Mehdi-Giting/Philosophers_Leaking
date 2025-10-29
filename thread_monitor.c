/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:14:34 by marvin            #+#    #+#             */
/*   Updated: 2025/10/29 14:41:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	long long	time;
	long long	last_meal;

	time = get_time(philo);
	pthread_mutex_lock(&philo->rules->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	if ((get_time_in_ms() - last_meal) > philo->rules->time_to_die)
	{
		pthread_mutex_lock(&philo->rules->print_lock);
		// pthread_mutex_lock(&philo->rules->start_lock);
		// printf("%lld %lld %lld.\n", philo->rules->start_time, get_time_in_ms(), get_time_in_ms() - philo->rules->start_time);
		// pthread_mutex_unlock(&philo->rules->start_lock);
		printf("%lld\n", (get_time_in_ms() - last_meal));
		printf("%lld %i has died.\n", time, philo->id);
		pthread_mutex_unlock(&philo->rules->print_lock);
		pthread_mutex_lock(&philo->rules->sim_lock);
		philo->rules->stop_sim = 1;
		pthread_mutex_unlock(&philo->rules->sim_lock);
		return (0);
	}
	return (1);
}

int	all_meals_eaten_check(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->rules->meal_eaten_lock);
	while (i < philo->rules->philo_count
		&& philo[i].meals_eaten >= philo->rules->must_eat_count)
		i++;
	pthread_mutex_unlock(&philo->rules->meal_eaten_lock);
	if (i == philo->rules->philo_count)
	{
		pthread_mutex_lock(&philo->rules->print_lock);
		printf("All meals have been eaten.\n");
		pthread_mutex_unlock(&philo->rules->print_lock);
		pthread_mutex_lock(&philo->rules->sim_lock);
		philo->rules->stop_sim = 1;
		pthread_mutex_unlock(&philo->rules->sim_lock);
		return (0);
	}
	return (1);
}

void	*thread_monitor(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(50);
		if (check_for_death(philo) == 1)
			return (NULL);
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
	}
	return (NULL);
}
