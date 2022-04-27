/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:57:22 by fgrossi           #+#    #+#             */
/*   Updated: 2022/04/27 14:22:33 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	pthread_t		check_death_thread;
	int				philo_n;
	int				last_eat;
	int				count;
	int				left_fork;
	int				right_fork;
	int				is_eating;
	pthread_mutex_t	mutex_eating;
	struct s_args	*table;
}				t_philo;

typedef struct s_args
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_must_eat;
	int				start;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	*forks;
	int				finish;
	t_philo			**philo;
}				t_args;

int			get_time(void);
void		message(t_args *table, int philo_n, char *msg);
void		ft_usleep(uint64_t time_in_ms);
t_args		*init(int ac, char **av);
void		take_fork(t_philo *ph);
void		eat(t_philo *ph);
int			check_num(char *string);
int			ft_atoi(const char *str);
int			check(char **av, int ac);

#endif