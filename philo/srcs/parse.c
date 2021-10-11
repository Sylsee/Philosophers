/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:48:23 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/05 01:09:09 by marvin           ###   ########.fr       */
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
	if (check_arg(argc, argv))
	{
		env->finish = 0;
		env->nb_philo = ft_atoi(argv[1]);
		env->die = ft_atoi(argv[2]);
		env->eat = ft_atoi(argv[3]);
		env->sleep = ft_atoi(argv[4]);
		env->m_eat = -1;
		if (argc == 6)
			env->m_eat = ft_atoi(argv[5]);
		if (env->nb_philo < 1 || env->nb_philo > 1000
			|| env->die < 1 || env->die > 999999
			|| env->eat < 1 || env->eat > 999999
			|| env->sleep < 1 || env->sleep > 999999
			|| ((env->m_eat < 1 || env->m_eat > 999999) && argc == 6))
			return (ft_exit("Error: Arguments must be positive and non-null",
					0));
		if (env->nb_philo > 2000)
			return (ft_exit("Error : There cannot be more than 2000\
philosophers", 0));
		return (1);
	}
	return (ft_exit("Error : Arguments must be positive and non-null", 0));
}
