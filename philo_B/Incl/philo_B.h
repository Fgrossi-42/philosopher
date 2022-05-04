/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_B.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:18:09 by fgrossi           #+#    #+#             */
/*   Updated: 2022/05/04 15:18:12 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	pid_t			philo_pid;
	pthread_t		check_death;
	int				philo_n;
	int				last_meal_time;
	sem_t			*sem_eat;
	struct s_args	*table;
}				t_philo;

typedef struct s_args
{
	pthread_t		check_eat;
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				t_to_eat;
	int				start;
	sem_t			*write;
	sem_t			*eat;
	sem_t			*forks;
	t_philo			**philo;
}				t_args;

int			get_time(void);
void		message(t_args *table, int philo_n, char *msg);
void		ft_usleep(uint64_t time_in_ms);
t_args		*init(int argc, char **argv);
void		take_fork(t_philo *ph);
void		eat(t_philo *ph);
void		go_to_bed(t_philo *ph);
int			is_digit(char *string);
int			ft_atoi(const char *str);
int			check(char **argv, int argc);
void		close_processes(t_args *table);

#endif
