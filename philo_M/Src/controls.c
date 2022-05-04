/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:40:19 by fgrossi           #+#    #+#             */
/*   Updated: 2022/04/29 12:17:24 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Incl/philo.h"

int	check(char **av, int ac)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error\n");
		return (1);
	}
	while (i < ac)
	{
		if (av[i][0] == '-' || check_num(av[i])
			|| ft_atoi(av[i]) == 0)
		{
			printf("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_check(unsigned long pt, int s)
{
	if (pt > 2147483647)
		return (-1);
	return (pt * s);
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

int	ft_atoi(const char *str)
{
	int	j;
	int	t_p;
	int	tt;

	tt = 1;
	j = 0;
	t_p = 0;
	if (*str == 27)
		return (0);
	if (*str == '-')
	{
		tt = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*(str + j)))
		t_p = t_p * 10 + (int)(*(str + j++) - '0');
	return (ft_check(t_p, tt));
}
