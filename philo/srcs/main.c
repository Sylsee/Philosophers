/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:10:03 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/29 22:08:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (!(parse(argc, argv, &env)))
		return (1);
	if (!(create_threads(argv, &env)))
		return (ft_exit("Error: Canno't create threads", 2));
	return (0);
}
