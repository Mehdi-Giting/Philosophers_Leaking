/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:03:06 by marvin            #+#    #+#             */
/*   Updated: 2025/10/26 20:45:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_rules *rules)
{
	printf("%ld 1 has taken a fork\n", get_time_in_ms() - rules->start_time);
	usleep(rules->time_to_die * 1000);
	printf("%ld 1 has died\n", get_time_in_ms() - rules->start_time);
	cleanup_all(NULL, rules);
}

int	main(int argc, char *argv[])
{
	t_rules		*rules;
	t_philo		*philo;
	pthread_t	monitor;

	if (is_valid_input(argc, argv) == 0)
	{
		printf("Inputs are invalid!\n");
		return (1);
	}
	rules = init_rules(argv);
	if (!rules)
		return (1);
	if (rules->philo_count == 1)
	{
		one_philo(rules);
		return (0);
	}
	rules->stop_sim = 0;
	philo = init_philo(rules);
	thread_creation(philo);
	pthread_create(&monitor, NULL, thread_monitor, philo);
	pthread_join(monitor, NULL);
	thread_join(philo);
	cleanup_all(philo, rules);
	return (0);
}
