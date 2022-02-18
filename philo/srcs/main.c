/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:10:03 by spoliart          #+#    #+#             */
/*   Updated: 2022/02/18 17:11:40 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_free(t_env *env, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&env->philo[i].eating);
		i++;
	}
	pthread_mutex_destroy(&env->print);
	free(env->philo);
	free(forks);
}

static void	one_philo(t_env env)
{
	printf("0ms 1 has taken a fork\n");
	ft_usleep(env.die, &env);
	printf("%dms 1 die\n", env.die);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_env			env;

	if (argc < 5 || argc > 6)
		return (internal_error("Usage: ./philo number_of_philosophers"
				" time_to_die time_to_eat time_to_sleep"
				" [number_of_times_each_philosopher_must_eat]"));
	if (!(parse(argc, argv, &env)))
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * env.nb_philo);
	if (!(initialize(&env, forks)))
		return (1);
	if (env.nb_philo == 1)
		one_philo(env);
	else if (threads(&env) == EXIT_FAILURE)
		return (internal_error("Error: Canno't create threads"));
	destroy_free(&env, forks);
	return (0);
}
