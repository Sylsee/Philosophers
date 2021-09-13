/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:48:23 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/13 02:51:15 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parse(int	argc, char **argv, t_philo *philo)
{
	philo->time_must_eat = ft_atoi(argv[--argc]);
	philo->time_to_sleep = ft_atoi(argv[--argc]);
	philo->time_to_eat = ft_atoi(argv[--argc]);
	philo->time_to_die = ft_atoi(argv[--argc]);
	philo->nb_philo = ft_atoi(argv[--argc]);
}
