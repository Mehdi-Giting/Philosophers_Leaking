/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:53:27 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 19:24:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sub_routine_sleeping(t_philo *philo)
{
	long long	time;
	
	time = get_time(philo);
	pthread_mutex_lock(&philo->rules->print_lock);
	printf("%lld %i is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	usleep(philo->rules->time_to_sleep * 1000);
}
