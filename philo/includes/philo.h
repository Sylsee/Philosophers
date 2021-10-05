/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:11:25 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/05 01:44:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	struct s_env	*env;
}				t_philo;

typedef struct s_env
{
	int				is_dead;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	long long		time_start;
	t_philo			*philo;
	pthread_mutex_t	print;
}				t_env;

int			parse(int argc, char **argv, t_env *env);
int			check_arg(int argc, char **argv);

int			initialize(t_env *env);

int			create_threads(t_env *env);

int			eat_routine(t_philo *philo);
int			think_routine(t_philo *philo);
int			sleep_routine(t_philo *philo);

void		ft_usleep(uint64_t miliseconds);
int			ft_atoi(const char *s);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
long long	ft_gettime(void);

int			ft_exit(char *s, int ret);

#endif
