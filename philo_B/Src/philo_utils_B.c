/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_B.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:17:28 by fgrossi           #+#    #+#             */
/*   Updated: 2022/05/04 15:17:30 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Incl/philo_B.h"

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	message(t_args *table, int philo_n, char *msg)
{
	sem_wait(table->write);
	printf("[%d]\tPhilosopher %d %s\n", get_time() - table->start,
		philo_n + 1, msg);
	if (msg[0] != 'd')
		sem_post(table->write);
}

void	ft_usleep(uint64_t time_in_ms)
{
	uint64_t	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(time_in_ms / 10);
}

int	is_digit(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] < '0' || string[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	close_processes(t_args *table)
{
	int	i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		while (i < table->n_philo)
			kill(table->philo[i++]->philo_pid, SIGKILL);
	}
}
