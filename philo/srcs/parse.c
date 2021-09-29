/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:48:23 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/29 22:05:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char **argv)
{
	int	i;

	while (--argc)
	{
		i = 0;
		while (argv[argc][i] >= '0' && argv[argc][i] <= '9')
			i++;
		if (argv[argc][i])
			return (0);
	}
	return (1);
}

int	parse(int argc, char **argv, t_env *env)
{
	if (argc != 5 || argc != 6 || !(check_arg(argc, argv)))
	{
		env->nb_philo = ft_atoi(argv[1]);
		env->die = ft_atoi(argv[2]);
		env->eat = ft_atoi(argv[3]);
		env->sleep = ft_atoi(argv[4]);
		env->m_eat = -1;
		if (argc == 6)
			env->m_eat = ft_atoi(argv[5]);
		if (env->nb_philo < 1 || env->time_to_die < 1 || env->time_to_eat < 1
			|| env->time_to_sleep < 1 || env->time_must_eat < 1)
			return (ft_exit("Error : Arguments must be positive and non-null",
					0));
		if (env->nb_philo > 2000)
			return (ft_exit("Error : It can't have more than 2000 philosophers",
					0));
		return (1);
	}
	return (ft_exit("Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]", 0));
}
