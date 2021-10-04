/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2021/10/05 00:27:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(int id, char *s)
{
	printf("%lld ", ft_time_ms());
	ft_putnbr_fd(id);
	ft_putendl_fd(s, 1);
}

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fork))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo->id, " has taking left fork");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	if (pthread_mutex_lock(&philo->r_fork))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo->id, " has taking right fork");
	write_action(philo->id, " is eating");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	ft_usleep(philo->env->eat);
	if (pthread_mutex_unlock(&philo->r_fork))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	if (pthread_mutex_unlock(&philo->l_fork))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
}

int	think(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo->id, " is thinking");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	ft_usleep(philo->env->think);
}

int	sleep(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 1));
	write_action(philo->id, " is sleeping");
	if (pthread_mutex_unlock(&philo->env->print))
		return (ft_exit("Error : pthread_mutex_unlock error", 1));
	ft_usleep(philo->env->sleep);
}
