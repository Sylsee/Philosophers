/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:35:44 by spoliart          #+#    #+#             */
/*   Updated: 2022/02/14 02:56:59 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__attribute__((always_inline)) inline int	internal_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
