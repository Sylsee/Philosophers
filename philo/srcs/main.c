/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:10:03 by spoliart          #+#    #+#             */
/*   Updated: 2022/02/13 20:21:49 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_free(t_env *env, pthread_mutex_t *tab)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		pthread_mutex_destroy(&tab[i]);
	pthread_mutex_destroy(&env->print);
	pthread_mutex_destroy(&env->eating);
	free(env->philo);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*tab;
	t_env			env;

	if (argc < 5 || argc > 6)
		return (ft_exit("Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]", 0));
	if (!(parse(argc, argv, &env)))
		return (1);
	tab = malloc(sizeof(pthread_mutex_t) * env.nb_philo);
	if (!(initialize(&env, tab)))
		return (1);
	if (threads(&env) == EXIT_FAILURE)
		return (ft_exit("Error: Canno't create threads", 2));
	destroy_free(&env, tab);
	return (0);
}
