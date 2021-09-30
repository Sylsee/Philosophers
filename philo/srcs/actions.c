/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:29:13 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 05:32:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think_sleep(t_env *env)
{
	if (pthread_mutex_lock(&env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 0));

	if (pthread_mutex_unlock(&env->print))
		return (ft_exit("Error : pthread_mutex_lock error", 0));
}

int actions(t_philo *philo)
{
	pthread
}
