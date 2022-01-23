/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2022/01/23 19:26:29 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
		ft_usleep(philo->env->eat / 10);
	while (philo->env->finish == false)
	{
		eat_routine(philo);
		if (philo->env->finish == true)
			break ;
		sleep_routine(philo);
		if (philo->env->finish == true)
			break ;
		think_routine(philo);
	}
	return (NULL);
}

static void	check_death(t_env *env, t_philo philo)
{
	pthread_mutex_lock(&env->eating);
	if (get_time() - philo.last_eat >= env->die)
	{
		pthread_mutex_lock(&env->print);
		write_action(env->time_start, philo.id, " die");
		env->finish = true;
		pthread_mutex_unlock(&env->print);
	}
	pthread_mutex_unlock(&env->eating);
}

static void	watcher(t_env *env)
{
	int	i;
	int	finish_eat;

	while (env->finish == false)
	{
		i = 0;
		finish_eat = 0;
		while (i < env->nb_philo && env->finish == false)
		{
			check_death(env, env->philo[i]);
			if (env->m_eat != -1 && env->philo[i].nb_eat >= env->m_eat)
			{
				finish_eat++;
				if (finish_eat == env->nb_philo)
					env->finish = true;
			}
			i++;
		}
	}
}

int	threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_create(&env->philo[i].thread, NULL, routine,
				&(env->philo[i])))
			return (ft_exit("Error : Cannot create threads", EXIT_FAILURE));
	}
	watcher(env);
	i = -1;
	if (env->nb_philo == 1)
	{
		if (pthread_detach(env->philo[0].thread))
			return (ft_exit("Error : Cannot detach threads", EXIT_FAILURE));
	}
	else
	{
		while (++i < env->nb_philo)
			if (pthread_join(env->philo[i].thread, NULL))
				return (ft_exit("Error : Cannot join threads", EXIT_FAILURE));
	}
	ft_usleep(10);
	return (EXIT_SUCCESS);
}
