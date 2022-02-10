/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:48:23 by spoliart          #+#    #+#             */
/*   Updated: 2022/02/10 13:40:40 by spoliart         ###   ########.fr       */
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
		env->nb_philo = ft_atoi(argv[1]);
		env->die = ft_atoi(argv[2]);
		env->eat = ft_atoi(argv[3]);
		env->sleep = ft_atoi(argv[4]);
		env->m_eat = -1;
		if (argc == 6)
			env->m_eat = ft_atoi(argv[5]);
		if (env->die < 1 || env->eat < 1 || env->sleep < 1
			|| ((env->m_eat < 1) && argc == 6))
			return (ft_exit("Error: Arguments must be positive and non-null",
					0));
		if (env->nb_philo > 200)
			return (ft_exit("Error : There cannot be more than 200\
philosophers", 0));
		return (1);
	}
	return (ft_exit("Error : Arguments must be positive and non-null", 0));
}
