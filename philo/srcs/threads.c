/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2022/02/14 01:51:19 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(&philo->env->print);
	while (philo->env->finish == false)
	{
		pthread_mutex_unlock(&philo->env->print);
		work(philo);
		pthread_mutex_lock(&philo->env->print);
	}
	pthread_mutex_unlock(&philo->env->print);
	return (NULL);
}

void	check_death(t_env *env, int i, int *finish_eat)
{
	pthread_mutex_lock(&env->eating);
	if (get_time() - env->philo[i].last_eat >= env->die)
	{
		write_action(env->time_start, &env->philo[i], " die");
		pthread_mutex_lock(&env->print);
		env->finish = true;
		pthread_mutex_unlock(&env->print);
	}
	pthread_mutex_unlock(&env->eating);
	pthread_mutex_lock(&env->print);
	if (env->m_eat != -1 && env->philo[i].nb_eat >= env->m_eat)
	{
		pthread_mutex_unlock(&env->print);
		(*finish_eat)++;
		if (*finish_eat == env->nb_philo)
		{
			pthread_mutex_lock(&env->print);
			env->finish = true;
			printf("Everybody ate %d times\n", env->m_eat);
			pthread_mutex_unlock(&env->print);
		}
	}
	else
		pthread_mutex_unlock(&env->print);
}

static void	watcher(t_env *env)
{
	int	i;
	int	finish_eat;

	pthread_mutex_lock(&env->print);
	while (env->finish == false)
	{
		i = 0;
		finish_eat = 0;
		while (env->finish == false && i < env->nb_philo)
		{
			pthread_mutex_unlock(&env->print);
			check_death(env, i, &finish_eat);
			i++;
			pthread_mutex_lock(&env->print);
		}
		pthread_mutex_unlock(&env->print);
		pthread_mutex_lock(&env->print);
	}
	pthread_mutex_unlock(&env->print);
}

int	threads(t_env *env)
{
	int	i;

	env->time_start = get_time();
	i = -1;
	while (++i < env->nb_philo)
	{
		env->philo[i].last_eat = env->time_start;
		if (pthread_create(&env->philo[i].thread, NULL, routine,
				&(env->philo[i])))
			return (internal_error("Error : Cannot create threads"));
	}
	watcher(env);
	if (env->nb_philo != 1)
	{
		i = -1;
		while (++i < env->nb_philo)
			if (pthread_join(env->philo[i].thread, NULL))
				return (internal_error("Error : Cannot join threads"));
		usleep(100);
	}
	return (EXIT_SUCCESS);
}
