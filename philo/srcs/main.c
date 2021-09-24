/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:10:03 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/24 23:30:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (!(parse(argv, &env)))
		return (1);
	if (!(create_threads(argv, &env)))
	{
		ft_putendl_fd("Error: Canno't create threads", 2);
		return (1);
	}
	if (!(philo(&env)))
	{
		ft_putendl_fd("", 2);
		return (1);
	}
	return (0);
}
