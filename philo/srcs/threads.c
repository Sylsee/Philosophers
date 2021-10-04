/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2021/10/05 00:29:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time_ms(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

int	check_death(t_philo *philo)
{
}

void	*routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
	{
		think(philo);
		sleep(philo);
	}
	while (check_death(philo))
	{
		eat(philo);
		think(philo);
		sleep(philo);
		usleep(100);
	}
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
		if (pthread_create(&env->philo[i].thread, NULL, routine, philo))
			return (ft_exit("Error : Cannot create threads", 0));
	i = -1;
	while (env->dead == 0)
		;
	while (++i < env->nb_philo)
		if (pthread_detach(env->philo[i].thread))
			return (ft_exit("Error : Cannot detach threads", 0));
	return (1);
}
