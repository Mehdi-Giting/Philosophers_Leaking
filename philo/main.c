/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:03:06 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 16:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if (is_valid_input(argc, argv))
		return (printf("Inputs are invalid!\n"), 1);
	if (one_philo(argv))
		return (0);
	if (parse_args(argc, argv, &rules))
		return (printf("Error: invalid args\n"), 1);
	if (rules_init(&rules))
		return (printf("Error: init rules\n"), 1);
	if (philos_init(&rules))
		return (printf("Error: init philos\n"), 1);
	if (start_simulation(&rules))
		printf("Error: simulation start failed\n");
	destroy_and_free(&rules);
	return (0);
}
