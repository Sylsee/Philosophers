/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2022/02/10 17:59:06 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < miliseconds)
		usleep(1);
}

static void	lock(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
}

static void	unlock(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
}

void	eat_routine(t_philo *philo)
{
	lock(philo);
	pthread_mutex_lock(&philo->env->eating);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->env->eating);
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
	{
		write_action(philo->env->time_start, philo->id,
			" has taken a fork");
		write_action(philo->env->time_start, philo->id,
			" has taken a fork");
		write_action(philo->env->time_start, philo->id, " is eating");
		pthread_mutex_unlock(&philo->env->print);
		ft_usleep(philo->env->eat);
		pthread_mutex_lock(&philo->env->print);
		philo->nb_eat++;
	}
	pthread_mutex_unlock(&philo->env->print);
	pthread_mutex_lock(&philo->env->eating);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->env->eating);
	unlock(philo);
}

void	sleep_think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
	{
		write_action(philo->env->time_start, philo->id, " is sleeping");
		pthread_mutex_unlock(&philo->env->print);
		ft_usleep(philo->env->sleep);
		pthread_mutex_lock(&philo->env->print);
	}
	pthread_mutex_unlock(&philo->env->print);
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
		write_action(philo->env->time_start, philo->id, " is thinking");
	pthread_mutex_unlock(&philo->env->print);
}
