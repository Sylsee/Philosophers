/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2022/02/13 22:41:39 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	swap_forks(pthread_mutex_t **l, pthread_mutex_t **r)
{
	pthread_mutex_t	*tmp;

	tmp = *l;
	*l = *r;
	*r = tmp;
}

static void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
	{
		swap_forks(&philo->l_fork, &philo->r_fork);
		ft_usleep(philo->env->eat / 5, philo->env);
	}
	pthread_mutex_lock(&philo->env->print);
	while (philo->env->finish == false)
	{
		pthread_mutex_unlock(&philo->env->print);
		eat_routine(philo);
		pthread_mutex_lock(&philo->env->print);
		if (philo->env->finish == true)
			break ;
		pthread_mutex_unlock(&philo->env->print);
		sleep_think_routine(philo);
		pthread_mutex_lock(&philo->env->print);
	}
	pthread_mutex_unlock(&philo->env->print);
	return (NULL);
}

static inline void	check_death(t_env *env, int i, int *finish_eat)
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
		usleep(10);
	}
	return (EXIT_SUCCESS);
}
