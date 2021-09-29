/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2021/09/29 22:13:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*init_threads(void *param)
{
	static int	id = 0;
	t_env	*env;

	env = (t_env *)param;
	env->philo[id].id = id;
	pthread_mutex_lock(env->print);
	printf("nb_philo: [%d]\nid: [%d]\n", env->nb_philo, env->philo[id].id);
	pthread_mutex_unlock(env->print);
	id++;
	return (NULL);
}

void	init_mutex(t_env *env)
{
	pthread_mutex_init(env->print, NULL);
}

int	create_threads(char **argv, t_env *env)
{
	int	i;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (ft_exit("Error : Malloc error", 0));
	init_mutex(env);
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_create(env->philo[i].thread, NULL, &init_threads, env))
			return (ft_exit("Error : Canno't create threads", 0));
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_detach(env->philo[i].thread, NULL))
			return (ft_exit("Error : Canno't join threads", 0));
	return (1);
}
