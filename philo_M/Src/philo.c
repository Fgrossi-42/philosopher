/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:47:03 by fgrossi           #+#    #+#             */
/*   Updated: 2022/04/27 15:47:06 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Incl/philo.h"

void	check_eat(t_philo	*ph)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&ph->mutex_eating);
	while (i < ph->table->n_philo)
	{
		if (ph->table->philo[i]->count >= ph->table->t_must_eat)
		{
			if (i == ph->table->n_philo - 1)
			{
				pthread_mutex_lock(&ph->table->mutex_write);
				ph->table->finish = 0;
			}
			i++;
		}
		else
			break ;
	}
	pthread_mutex_unlock(&ph->mutex_eating);
}

void	*check_death(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (ph->table->finish)
	{
		if (!(ph->is_eating)
			&& get_time() - ph->last_eat >= ph->table->t_die)
		{
			pthread_mutex_lock(&ph->mutex_eating);
			message(ph->table, ph->philo_n, "died");
			ph->table->finish = 0;
			pthread_mutex_unlock(&ph->mutex_eating);
		}
		if (ph->table->t_must_eat
			&& ph->count >= ph->table->t_must_eat)
			check_eat(ph);
		ft_usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (ph->table->finish)
	{
		take_fork(ph);
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
		message(ph->table, ph->philo_n, "is sleeping");
		ft_usleep(ph->table->t_sleep);
		message(ph->table, ph->philo_n, "is thinking");
	}
	return (NULL);
}

void	start_philo(t_args *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philo[i]->last_eat = get_time();
		pthread_create(&table->philo[i]->philo_thread, NULL, routine,
			(void *)table->philo[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < table->n_philo)
	{
		pthread_create(&table->philo[i]->check_death_thread, NULL, check_death,
			(void *)table->philo[i]);
		i++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	t_args		*table;

	if (check(av, ac))
		return (1);
	table = init(ac, av);
	if (!table)
		return (1);
	table->finish = 1;
	table->start = get_time();
	start_philo(table);
	while (table->finish)
		continue ;
	return (0);
}
