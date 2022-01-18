/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2022/01/18 18:36:27 by spoliart         ###   ########.fr       */
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
		if (eat_routine(philo) != 0)
			break ;
		if (philo->env->finish == true)
			break ;
		if (sleep_routine(philo) != 0)
			break ;
		if (philo->env->finish == true)
			break ;
		if (think_routine(philo) != 0)
			break ;
	}
	return (NULL);
}

static void	check_death(t_env *env, t_philo philo, int *finish_eat)
{
	pthread_mutex_lock(&env->eating);
	if (get_time() - philo.last_eat >= env->die)
	{
		if (pthread_mutex_lock(&env->print))
			return ;
		write_action(env->time_start, philo.id, " die");
		env->finish = true;
		if (pthread_mutex_unlock(&env->print))
			return ;
	}
	pthread_mutex_unlock(&env->eating);
	if (env->m_eat != -1 && philo.nb_eat >= env->m_eat)
	{
		(*finish_eat)++;
		if (*finish_eat == env->nb_philo)
			env->finish = true;
	}
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
			check_death(env, env->philo[i], &finish_eat);
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
