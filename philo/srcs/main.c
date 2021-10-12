/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:10:03 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/12 09:34:08 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_free(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		pthread_mutex_destroy(&env->philo[i].l_fork);
	pthread_mutex_destroy(&env->print);
	free(env->philo);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 5 && argc > 6)
		return (ft_exit("Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]", 0));
	if (!(parse(argc, argv, &env)))
		return (1);
	if (!(initialize(&env)))
		return (1);
	if (!(threads(&env)))
		return (ft_exit("Error: Canno't create threads", 2));
	destroy_free(&env);
	return (0);
}
