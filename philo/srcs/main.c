/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:10:03 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/14 11:50:19 by spoliart         ###   ########.fr       */
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

void	create_threads(char **argv, t_philo *philo)
{
	int	i;
	pthread_t *threads;

	philo->nb_philo = ft_atoi(argv[1]);
	i = philo->nb_philo;
	threads = malloc(sizeof(pthread_t) * i);
	if (!threads)
		print_and_exit("Malloc error");
	while (i && !(pthread_create(threads[i], NULL, )))
	{
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc != 6 || !(check_arg(argc, argv)))
		print_and_exit("Usage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
	philo = malloc(sizeof(t_philo));
	if (!philo)
		print_and_exit("Malloc error");
	create_threads(argv, &philo);
	return (0);
}
