/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2022/02/13 19:33:17 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(uint64_t miliseconds, t_env *env)
{
	uint64_t	start;

	pthread_mutex_lock(&env->print);
	if (env->finish == false)
	{
		pthread_mutex_unlock(&env->print);
		start = get_time();
		while (get_time() - start < miliseconds)
			usleep(1);
	}
	else
		pthread_mutex_unlock(&env->print);
}

void	write_action(long long time, t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
	{
		ft_putnbr_fd(get_time() - time, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd("\n", 1);
	}
	pthread_mutex_unlock(&philo->env->print);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	write_action(philo->env->time_start, philo, " has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	write_action(philo->env->time_start, philo, " has taken a fork");
	pthread_mutex_lock(&philo->env->eating);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->env->eating);
	write_action(philo->env->time_start, philo, " is eating");
	ft_usleep(philo->env->eat, philo->env);
	pthread_mutex_lock(&philo->env->print);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->env->print);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think_routine(t_philo *philo)
{
	write_action(philo->env->time_start, philo, " is sleeping");
	ft_usleep(philo->env->sleep, philo->env);
	write_action(philo->env->time_start, philo, " is thinking");
}
