/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2021/10/05 03:25:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_action(t_philo *philo, int id, char *s)
{
	printf("%lld ", ft_gettime() - philo->env->time_start);
	ft_putnbr_fd(id, 1);
	ft_putendl_fd(s, 1);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = ft_gettime();
	while (ft_gettime() - start < miliseconds)
		usleep(1);
}

int	eat_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fork))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo, philo->id, " has taking left fork");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	if (pthread_mutex_lock(&philo->r_fork))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo, philo->id, " has taking right fork");
	write_action(philo, philo->id, " is eating");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	ft_usleep(philo->env->eat);
	if (pthread_mutex_unlock(&philo->r_fork))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	if (pthread_mutex_unlock(&philo->l_fork))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
}

int	think_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo, philo->id, " is thinking");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
}

int	sleep_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo, philo->id, " is sleeping");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	ft_usleep(philo->env->sleep);
}
