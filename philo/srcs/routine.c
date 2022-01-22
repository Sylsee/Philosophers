/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2022/01/22 12:11:42 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(long long time, int id, char *s)
{
	ft_putnbr_fd(get_time() - time, 1);
	ft_putstr_fd("ms: ", 1);
	ft_putnbr_fd(id, 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < miliseconds)
		usleep(1);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->env->eating);
	philo->last_eat = get_time();
	if (philo->env->finish == false)
	{
		pthread_mutex_lock(&philo->env->print);
		write_action(philo->env->time_start, philo->id,
			" has taking left fork");
		write_action(philo->env->time_start, philo->id,
			" has taking right fork");
		write_action(philo->env->time_start, philo->id, " is eating");
		pthread_mutex_unlock(&philo->env->print);
	}
	pthread_mutex_unlock(&philo->env->eating);
	if (philo->env->finish == false)
		ft_usleep(philo->last_eat - get_time() + philo->env->eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->nb_eat++;
}

void	think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
		write_action(philo->env->time_start, philo->id, " is thinking");
	pthread_mutex_unlock(&philo->env->print);
}

void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
		write_action(philo->env->time_start, philo->id, " is sleeping");
	pthread_mutex_unlock(&philo->env->print);
	if (philo->env->finish == false)
		ft_usleep(philo->env->sleep);
}
