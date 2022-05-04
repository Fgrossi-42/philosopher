/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_B.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:17:13 by fgrossi           #+#    #+#             */
/*   Updated: 2022/05/04 15:17:14 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Incl/philo_B.h"

void	*check_eat(void *args)
{
	t_args	*table;
	int		eat_counter;
	int		i;

	table = (t_args *)args;
	eat_counter = 0;
	while (eat_counter < table->t_to_eat)
	{
		i = 0;
		while (i <= table->n_philo)
		{
			sem_wait(table->eat);
			i++;
		}
		eat_counter++;
	}
	sem_wait(table->write);
	i = 0;
	while (i < table->n_philo)
		kill(table->philo[i++]->philo_pid, SIGKILL);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (1)
	{
		sem_wait(ph->sem_eat);
		if (get_time() - ph->last_meal_time >= ph->table->t_death)
		{
			message(ph->table, ph->philo_n, "died");
			exit(1);
		}
		sem_post(ph->sem_eat);
		usleep(100);
	}
	return (NULL);
}

void	*routine(t_philo	*ph)
{
	while (1)
	{
		take_fork(ph);
		sem_post(ph->table->forks);
		sem_post(ph->table->forks);
		message(ph->table, ph->philo_n, "is sleeping");
		ft_usleep(ph->table->t_sleep);
		message(ph->table, ph->philo_n, "is thinking");
		usleep(100);
	}
	return (NULL);
}

void	start_philo(t_args	*table)
{
	int	i;

	i = 0;
	if (table->t_to_eat)
		pthread_create(&table->check_eat, NULL, check_eat,
			(void *)table);
	while (i < table->n_philo)
	{
		table->philo[i]->philo_pid = fork();
		table->philo[i]->last_meal_time = get_time();
		if (table->philo[i]->philo_pid == 0)
		{
			pthread_create(&table->philo[i]->check_death, NULL, check_death,
				(void *)table->philo[i]);
			routine(table->philo[i]);
			exit(1);
		}
		i++;
		usleep(100);
	}
	close_processes(table);
}

int	main(int argc, char **argv)
{
	t_args		*table;

	if (check(argv, argc))
		return (1);
	table = init(argc, argv);
	if (!table)
		return (1);
	table->start = get_time();
	start_philo(table);
	return (0);
}
