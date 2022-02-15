/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2022/02/15 18:34:08 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(&philo->env->finish);
	while (philo->env->is_finish == false)
	{
		pthread_mutex_unlock(&philo->env->finish);
		work(philo);
		pthread_mutex_lock(&philo->env->finish);
	}
	pthread_mutex_unlock(&philo->env->finish);
	return (NULL);
}

static void	check_death(t_env *env, t_philo philo)
{
	pthread_mutex_lock(&philo.eating);
	if (get_time() - philo.last_eat >= env->die)
	{
		pthread_mutex_unlock(&philo.eating);
		write_action(env->time_start, &philo, " die");
		pthread_mutex_lock(&env->finish);
		env->is_finish = true;
		pthread_mutex_unlock(&env->finish);
	}
	else
		pthread_mutex_unlock(&philo.eating);
}

static void	check_must_eat(t_env *env, t_philo philo, int *finish_eat)
{
	pthread_mutex_lock(&philo.eating);
	if (philo.nb_eat >= env->m_eat)
	{
		pthread_mutex_unlock(&philo.eating);
		(*finish_eat)++;
		if (*finish_eat == env->nb_philo)
		{
			pthread_mutex_lock(&env->finish);
			env->is_finish = true;
			pthread_mutex_lock(&env->print);
			printf("Every philosophers ate %d times\n", env->m_eat);
			pthread_mutex_unlock(&env->print);
			pthread_mutex_unlock(&env->finish);
		}
	}
	else
		pthread_mutex_unlock(&philo.eating);
}

static void	watcher(t_env *env)
{
	int	i;
	int	finish_eat;

	pthread_mutex_lock(&env->finish);
	while (env->is_finish == false)
	{
		i = 0;
		finish_eat = 0;
		while (env->is_finish == false && i < env->nb_philo)
		{
			pthread_mutex_unlock(&env->finish);
			check_death(env, env->philo[i]);
			if (env->m_eat != -1)
				check_must_eat(env, env->philo[i], &finish_eat);
			i++;
			pthread_mutex_lock(&env->finish);
		}
	}
	pthread_mutex_unlock(&env->finish);
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
