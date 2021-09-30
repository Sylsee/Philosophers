/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 04:45:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *param)
{
	static int	id = 0;
	t_env		*env;

	env = (t_env *)param;
	printf("yesso\n");
	pthread_mutex_lock(&env->print);
	printf("yessa\n");
	pthread_mutex_unlock(&env->print);
	fflush(stdout);
	id++;
	return (NULL);
}

int	create_threads(t_env *env)
{
	int	i;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (ft_exit("Error : Malloc error", 0));
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_create(&env->philo[i].thread, NULL, thread, env))
			return (ft_exit("Error : Cannot create threads", 0));
	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_detach(env->philo[i].thread))
			return (ft_exit("Error : Cannot detach threads", 0));
		printf("c fini\n");
		fflush(stdout);
	}
	return (1);
}
