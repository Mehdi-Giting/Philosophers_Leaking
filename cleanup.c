/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:03:34 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 17:27:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_and_free(t_rules *rules)
{
	int	i;

	if (rules->forks)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			pthread_mutex_destroy(&rules->philos[i].meal_mutex);
			i++;
		}
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->stop_mutex);
		free(rules->forks);
		rules->forks = NULL;
	}
	if (rules->philos)
	{
		free(rules->philos);
		rules->philos = NULL;
	}
}
