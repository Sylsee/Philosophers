/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 02:15:48 by marvin            #+#    #+#             */
/*   Updated: 2021/10/13 04:23:41 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_initialize(t_env *env)
{
	if (pthread_mutex_init(&env->print, NULL))
		return (ft_exit("Error : Fail to init mutex", 0));
	if (pthread_mutex_init(&env->finish, NULL))
		return (ft_exit("Error : Fail to init mutex", 0));
	return (1);
}

int	initialize(t_env *env)
{
	int	id;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (ft_exit("Malloc error", 0));
	env->time_start = get_time();
	env->finish = 0;
	id = 0;
	while (id < env->nb_philo)
	{
		env->philo[id].id = id + 1;
		env->philo[id].eating = 0;
		env->philo[id].last_eat = env->time_start;
		env->philo[id].nb_eat = 0;
		env->philo[id].env = &(*env);
		if (pthread_mutex_init(&env->philo[id].l_fork, NULL))
			return (ft_exit("Error : Fail to init mutex", 0));
		if (id == env->nb_philo - 1)
			env->philo[id].r_fork = &env->philo[0].l_fork;
		else
			env->philo[id].r_fork = &env->philo[id + 1].l_fork;
		id++;
	}
	return (mutex_initialize(env));
}
