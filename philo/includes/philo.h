/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 02:11:25 by spoliart          #+#    #+#             */
/*   Updated: 2022/02/13 20:23:51 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_env	*env;
}				t_philo;

typedef struct s_env
{
	bool			finish;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	long long		time_start;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	eating;
}				t_env;

int			parse(int argc, char **argv, t_env *env);
int			check_arg(int argc, char **argv);

int			initialize(t_env *env, pthread_mutex_t *tab);

int			threads(t_env *env);

void		eat_routine(t_philo *philo);
void		sleep_think_routine(t_philo *philo);

void		write_action(long long time, t_philo *philo, char *s);
void		ft_usleep(uint64_t miliseconds, t_env *env);
int			ft_atoi(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long n, int fd);
long long	get_time(void);

int			ft_exit(char *s, int ret);

#endif
