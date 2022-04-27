/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:57:11 by fgrossi           #+#    #+#             */
/*   Updated: 2022/04/27 14:36:16 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	message(t_args *table, int philo_n, char *msg)
{
	pthread_mutex_lock(&table->mutex_write);
	printf("[%d]\tPhilosopher %d %s\n", get_time() - table->start,
		philo_n + 1, msg);
	if (msg[0] != 'd')
		pthread_mutex_unlock(&table->mutex_write);
}

void	ft_usleep(uint64_t time_in_ms)
{
	uint64_t	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(time_in_ms / 10);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
