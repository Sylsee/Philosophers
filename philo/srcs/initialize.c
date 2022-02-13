/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 02:15:48 by marvin            #+#    #+#             */
/*   Updated: 2022/02/13 20:20:05 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_initialize(t_env *env)
{
	if (pthread_mutex_init(&env->print, NULL))
		return (ft_exit("Error : Fail to init mutex", 0));
	if (pthread_mutex_init(&env->eating, NULL))
		return (ft_exit("Error : Fail to init mutex", 0));
	return (1);
}

int	initialize(t_env *env, pthread_mutex_t *tab)
{
	int	id;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (ft_exit("Malloc error", 0));
	env->time_start = get_time();
	env->finish = false;
	id = 0;
	while (id < env->nb_philo)
	{
		env->philo[id].id = id + 1;
		env->philo[id].last_eat = env->time_start;
		env->philo[id].nb_eat = 0;
		env->philo[id].env = &(*env);
		env->philo[id].r_fork = NULL;
		if (pthread_mutex_init(&tab[id], NULL))
			return (ft_exit("Error : Fail to init mutex", 0));
		env->philo[id].l_fork = &tab[id];
		if (id == env->nb_philo - 1)
			env->philo[id].r_fork = &tab[0];
		else
			env->philo[id].r_fork = &tab[id + 1];
		id++;
	}
	return (mutex_initialize(env));
}
