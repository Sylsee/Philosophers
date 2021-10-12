/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2021/10/12 06:09:46 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(long long time_start, int id, char *s)
{
	ft_putnbr_fd(get_time() - time_start, 1);
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
	if (philo->env->finish != 0)
		return (0);
	pthread_mutex_lock(&philo->l_fork);
	if (philo->env->finish != 0)
		return (0);
	pthread_mutex_lock(&philo->env->print);
	write_action(philo->env->time_start, philo->id, " has taking left fork");
	pthread_mutex_unlock(&philo->env->print);
	if (philo->env->finish != 0)
		return (0);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->env->print);
	philo->eating = 1;
	write_action(philo->env->time_start, philo->id, " has taking right fork");
	write_action(philo->env->time_start, philo->id, " is eating");
	pthread_mutex_unlock(&philo->env->print);
	if (philo->env->finish != 0)
		return (0);
	ft_usleep(philo->env->eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->last_eat = get_time();
	philo->eating = 0;
	philo->nb_eat++;
	return (0);
}

int	think_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo->env->time_start, philo->id, " is thinking");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	return (0);
}

int	sleep_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo->env->time_start, philo->id, " is sleeping");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	ft_usleep(philo->env->sleep);
	return (0);
}
