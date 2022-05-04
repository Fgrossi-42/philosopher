/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2_B.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:17:21 by fgrossi           #+#    #+#             */
/*   Updated: 2022/05/04 15:17:23 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Incl/philo_B.h"

int	check(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (1);
	}
	while (i < argc)
	{
		if (argv[i][0] == '-' || is_digit(argv[i])
			|| ft_atoi(argv[i]) == 0)
		{
			printf("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

t_philo	**philo_init(t_args *table)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * table->n_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < (int)table->n_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (0);
		philo[i]->philo_n = i;
		philo[i]->table = table;
		sem_unlink("eat counter");
		philo[i]->sem_eat = sem_open("eat counter", O_CREAT, 0644, 1);
		if (philo[i]->sem_eat == SEM_FAILED)
			return (NULL);
		i++;
	}
	return (philo);
}

int	sems_init(t_args *table)
{
	sem_unlink("forking");
	table->forks = sem_open("forking", O_CREAT, 0644,
			table->n_philo);
	if (table->forks == SEM_FAILED)
		return (1);
	sem_unlink("writing");
	table->write = sem_open("writing", O_CREAT, 0644, 1);
	if (table->write == SEM_FAILED)
		return (1);
	sem_unlink("meal");
	table->eat = sem_open("meal", O_CREAT, 0644, 1);
	if (table->eat == SEM_FAILED)
		return (1);
	return (0);
}

t_args	*init(int argc, char **argv)
{
	t_args	*table;

	table = malloc(sizeof(t_args) * 1);
	if (!table)
		return (NULL);
	table->n_philo = (uint64_t)ft_atoi(argv[1]);
	table->t_death = (uint64_t)ft_atoi(argv[2]);
	table->t_eat = (uint64_t)ft_atoi(argv[3]);
	table->t_sleep = (uint64_t)ft_atoi(argv[4]);
	if (table->n_philo == -1 || table->t_death == -1
		|| table->t_eat == -1 || table->t_sleep == -1
		|| table->t_to_eat == -1)
	{
		printf("Error\n");
		return (NULL);
	}
	table->t_to_eat = 0;
	if (argc == 6)
		table->t_to_eat = ft_atoi(argv[5]);
	if (sems_init(table))
		return (NULL);
	table->start = get_time();
	table->philo = philo_init(table);
	return (table);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->table->forks);
	message(philo->table, philo->philo_n, "has taken the left fork");
	sem_wait(philo->table->forks);
	message(philo->table, philo->philo_n, "has taken the right fork");
	message(philo->table, philo->philo_n, "is eating");
	sem_wait(philo->sem_eat);
	sem_post(philo->table->eat);
	philo->last_meal_time = get_time();
	ft_usleep(philo->table->t_eat);
	sem_post(philo->sem_eat);
}
