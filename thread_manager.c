/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:14:34 by marvin            #+#    #+#             */
/*   Updated: 2025/10/26 20:50:37 by marvin           ###   ########.fr       */
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

void	*thread_monitor(void *arg)
{
	int		i;
	int		time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->rules->stop_sim == 0)
	{
		i = 0;
		while (i < philo->rules->philo_count)
		{
			time = get_time_in_ms() - philo[i].last_meal_time;
			if (time > philo->rules->time_to_die)
			{
				pthread_mutex_lock(&philo[i].rules->print_lock);
				printf("%i has died, ending sim now.\n", philo[i].id);
				pthread_mutex_unlock(&philo[i].rules->print_lock);
				philo->rules->stop_sim = 1;
				break ;
			}
			else
				i++;
		}
		usleep(1000);
	}
	return (NULL);
}
