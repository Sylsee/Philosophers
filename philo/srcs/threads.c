/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2022/01/27 21:52:47 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
		ft_usleep(philo->env->eat / 10);
	pthread_mutex_lock(&philo->env->m_finish);
	while (philo->env->finish == false)
	{
		pthread_mutex_unlock(&philo->env->m_finish);
		eat_routine(philo);
		pthread_mutex_lock(&philo->env->m_finish);
		if (philo->env->finish == true)
			break ;
		pthread_mutex_unlock(&philo->env->m_finish);
		sleep_routine(philo);
		pthread_mutex_lock(&philo->env->m_finish);
		if (philo->env->finish == true)
			break ;
		pthread_mutex_unlock(&philo->env->m_finish);
		think_routine(philo);
		pthread_mutex_lock(&philo->env->m_finish);
	}
	pthread_mutex_unlock(&philo->env->m_finish);
	return (NULL);
}

static void	check_death(t_env *env, t_philo philo, int *finish_eat)
{
	pthread_mutex_lock(&env->eating);
	if (get_time() - philo.last_eat >= env->die)
	{
		pthread_mutex_lock(&env->print);
		write_action(env->time_start, philo.id, " die");
		pthread_mutex_unlock(&env->print);
		pthread_mutex_lock(&env->m_finish);
		env->finish = true;
		pthread_mutex_unlock(&env->m_finish);
	}
	pthread_mutex_unlock(&env->eating);
	if (env->m_eat != -1 && philo.nb_eat >= env->m_eat)
	{
		(*finish_eat)++;
		if (*finish_eat == env->nb_philo)
		{
			pthread_mutex_lock(&env->m_finish);
			env->finish = true;
			pthread_mutex_unlock(&env->m_finish);
		}
	}
}

static void	watcher(t_env *env)
{
	int	i;
	int	finish_eat;

	pthread_mutex_lock(&env->m_finish);
	while (env->finish == false)
	{
		pthread_mutex_unlock(&env->m_finish);
		i = 0;
		finish_eat = 0;
		pthread_mutex_lock(&env->m_finish);
		while (env->finish == false && i < env->nb_philo)
		{
			pthread_mutex_unlock(&env->m_finish);
			check_death(env, env->philo[i], &finish_eat);
			i++;
			pthread_mutex_lock(&env->m_finish);
		}
		pthread_mutex_unlock(&env->m_finish);
		pthread_mutex_lock(&env->m_finish);
	}
	pthread_mutex_unlock(&env->m_finish);
}

int	threads(t_env *env)
{
	int	i;

	if (env->nb_philo != 1)
	{
		i = -1;
		while (++i < env->nb_philo)
		{
			if (pthread_create(&env->philo[i].thread, NULL, routine,
					&(env->philo[i])))
				return (ft_exit("Error : Cannot create threads", EXIT_FAILURE));
		}
	}
	watcher(env);
	if (env->nb_philo != 1)
	{
		i = -1;
		while (++i < env->nb_philo)
			if (pthread_join(env->philo[i].thread, NULL))
				return (ft_exit("Error : Cannot join threads", EXIT_FAILURE));
		ft_usleep(10);
	}
	return (EXIT_SUCCESS);
}
