/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2021/10/11 08:15:59 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
		ft_usleep(philo->env->eat / 10);
	while (philo->env->finish == 0)
	{
		if (eat_routine(philo) != 0)
			break ;
		if (philo->env->finish != 0)
			break ;
		if (sleep_routine(philo) != 0)
			break ;
		if (philo->env->finish != 0)
			break ;
		if (think_routine(philo) != 0)
			break ;
	}
	return (NULL);
}

static void	watcher(t_env *env)
{
	int		i;
	t_philo	*philo;

	while (env->finish == 0)
	{
		i = 0;
		while (i < env->nb_philo && env->finish == 0)
		{
			philo = &env->philo[i];
			if (philo->eating == 0 && get_time() - philo->last_eat >= env->die)
			{
				if (pthread_mutex_lock(&env->print))
					return ;
				write_action(philo->env->time_start, philo->id, " die");
				if (pthread_mutex_unlock(&env->print))
					return ;
				env->finish = 1;
			}
			if (philo->nb_eat == env->m_eat)
				env->finish = 2;
			i++;
		}
	}
}

int	threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		if (pthread_create(&env->philo[i].thread, NULL, routine,
				&(env->philo[i])))
			return (ft_exit("Error : Cannot create threads", 0));
	watcher(env);
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_join(env->philo[i].thread, NULL))
			return (ft_exit("Error : Cannot detach threads", 0));
	ft_usleep(10);
	return (1);
}
