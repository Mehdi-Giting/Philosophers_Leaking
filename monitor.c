/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:16:18 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 17:18:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	all_philos_full(t_rules *rules)
{
	int	i;

	if (rules->must_eat == -1)
		return (false);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].meals_eaten < rules->must_eat)
		{
			pthread_mutex_unlock(&rules->philos[i].meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	return (true);
}

static bool	check_death(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo && !get_stop(rules))
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if ((now_ms() - rules->philos[i].last_meal_ms) > rules->time_to_die)
		{
			set_stop(rules, true);
			pthread_mutex_lock(&rules->print_mutex);
			printf("%ld %ld\n", now_ms() - rules->philos[i].last_meal_ms,
				rules->time_to_die + 5);
			pthread_mutex_unlock(&rules->philos[i].meal_mutex);
			printf("%ld %d died\n",
				now_ms() - rules->start_time_ms, rules->philos[i].id);
			pthread_mutex_unlock(&rules->print_mutex);
			return (true);
		}
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	while (!get_stop(rules))
	{
		if (check_death(rules))
			break ;
		if (all_philos_full(rules))
		{
			set_stop(rules, true);
			pthread_mutex_lock(&rules->print_mutex);
			printf("All philosophers have eaten\n");
			pthread_mutex_unlock(&rules->print_mutex);
			break ;
		}
		usleep(2000);
	}
	return (NULL);
}
