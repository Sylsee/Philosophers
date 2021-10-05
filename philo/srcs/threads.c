/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2021/10/05 03:25:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	if (ft_gettime() - philo->env->time_start >= philo->env->die)
	{
		philo->env->is_dead = 1;
		return (1);
	}
	return (0);
}

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
		ft_usleep(philo->env->eat);
	while (check_death(philo) == 0)
	{
		if (eat_routine(philo) != 0)
			return (NULL);
		if (sleep_routine(philo) != 0)
			return (NULL);
		if (think_routine(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

static void	watcher(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->env->is_dead == 0)
	{
		if (philo->eating == 0
			&& ft_gettime() - philo->last_eat >= philo->env->die)
		{
			if (pthread_mutex_lock(&philo->env->print))
				return (NULL);
			write_action(philo, philo->id, " die");
			if (pthread_mutex_unlock(&philo->env->print))
				return (NULL);
			philo->env->is_dead = 1;
		}
	}
}

int	create_threads(t_env *env)
{
	int	i;

	env->philo = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philo)
		return (ft_exit("Error : Malloc error", 0));
	i = -1;
	env->time_start = ft_gettime();
	while (++i < env->nb_philo)
		if (pthread_create(&env->philo[i].thread, NULL, routine,
				&env->philo[i]))
			return (ft_exit("Error : Cannot create threads", 0));
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_create(&env->philo[i].thread, NULL, watcher,
				&env->philo[i]))
			return (ft_exit("Error : Cannot create threads", 0));
	while (env->is_dead == 0)
		;
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_detach(env->philo[i].thread))
			return (ft_exit("Error : Cannot detach threads", 0));
	return (1);
}
