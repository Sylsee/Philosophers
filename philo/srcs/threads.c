/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <spoliart@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:19:23 by marvin            #+#    #+#             */
/*   Updated: 2021/09/24 23:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*init_threads(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	printf("nb_philo: [%d]\n", env->nb_philo);
	return (NULL);
}

int	create_threads(char **argv, t_philo *philo)
{
	int	i;

	env->philo = malloc(sizeof(t_philo) * philo->nb_philo);
	if (!env->philo)
		return (ft_exit("Error : Malloc error", 0));
	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_create(env->philo[i]->thread, NULL, &init_threads, env))
			return (ft_exit("Error : Canno't create threads", 0));
		if (pthread_join(env->philo[i]->thread, NULL))
			return (ft_exit("Error : Canno't join threads", 0));
	}
	return (1);
}
