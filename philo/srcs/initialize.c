/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 02:15:48 by marvin            #+#    #+#             */
/*   Updated: 2022/02/14 02:57:48 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_env *env, pthread_mutex_t *forks, int i)
{
	if (i % 2)
	{
		env->philo[i].r_fork = &forks[i];
		if (i < env->nb_philo - 1)
			env->philo[i].l_fork = &forks[i + 1];
		else
			env->philo[i].l_fork = &forks[0];
	}
	else
	{
		env->philo[i].l_fork = &forks[i];
		if (i < env->nb_philo - 1)
			env->philo[i].r_fork = &forks[i + 1];
		else
			env->philo[i].r_fork = &forks[0];
	}
}

static int	initialize_mutex(t_env *env, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		init_forks(env, forks, i);
		i++;
	}
	if (pthread_mutex_init(&env->print, NULL))
		return (internal_error("Error : Fail to init mutex"));
	if (pthread_mutex_init(&env->eating, NULL))
		return (internal_error("Error : Fail to init mutex"));
	return (1);
}

int	initialize(t_env *env, pthread_mutex_t *forks)
{
	int	id;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (internal_error("Malloc error"));
	env->finish = false;
	id = 0;
	while (id < env->nb_philo)
	{
		env->philo[id].id = id + 1;
		env->philo[id].nb_eat = 0;
		env->philo[id].env = &(*env);
		if (pthread_mutex_init(&forks[id], NULL))
			return (internal_error("Error : Fail to init mutex"));
		id++;
	}
	return (initialize_mutex(env, forks));
}
