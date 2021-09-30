/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 02:15:48 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 03:49:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_initialize(t_env *env)
{
	if (pthread_mutex_init(&env->print, NULL))
		return (ft_exit("Error : Fail to init mutex", 0));
	return (1);
}

int	initialize(t_env *env)
{
	int	id;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (ft_exit("Malloc error", 0));
	id = 0;
	while (id < env->nb_philo)
	{
		env->philo[id].id = id + 1;
		if (pthread_mutex_init(&env->philo[id].l_fork, NULL))
			return (ft_exit("Error : Fail to init mutex", 0));
		if (id != 0)
			env->philo[id - 1].r_fork = env->philo[id].l_fork;
		id++;
	}
	if (env->nb_philo > 1)
		env->philo[0].r_fork = env->philo[id - 1].l_fork;
	return (mutex_initialize(env));
}
