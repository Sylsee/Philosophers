/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:11:25 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/29 22:08:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	pthread_t		*thread;
	pthread_mutex_t	*f_left;
	pthread_mutex_t	*f_right;
}				t_philo;

typedef struct s_env
{
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	t_philo			*philo;
	pthread_mutex_t	*print;
}				t_env;

int		parse(int argc, char **argv, t_env *env);
int		check_arg(int argc, char **argv);

int		create_threads(char **argv, t_env *env);

int		ft_atoi(const char *s);

int		ft_exit(char *s, int ret);

#endif
