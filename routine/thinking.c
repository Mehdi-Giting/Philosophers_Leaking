/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:51:09 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 19:24:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sub_routine_thinking(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	pthread_mutex_lock(&philo->rules->print_lock);
	printf("%lld %i is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
}