/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2022/01/16 18:10:07 by spoliart         ###   ########.fr       */
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

int	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->env->print);
	if (philo->env->finish == false)
	{
		write_action(philo->env->time_start, philo->id,
			" has taking left fork");
		write_action(philo->env->time_start, philo->id,
			" has taking right fork");
		write_action(philo->env->time_start, philo->id, " is eating");
	}
	pthread_mutex_unlock(&philo->env->print);
	philo->eating = true;
	if (philo->env->finish == false)
		ft_usleep(philo->env->eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->eating = false;
	philo->last_eat = get_time();
	philo->nb_eat++;
	return (0);
}

int	think_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	if (philo->env->finish == false)
		write_action(philo->env->time_start, philo->id, " is thinking");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	return (0);
}

int	sleep_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	if (philo->env->finish == false)
		write_action(philo->env->time_start, philo->id, " is sleeping");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	if (philo->env->finish == false)
		ft_usleep(philo->env->sleep);
	return (0);
}
