/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_B.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:17:04 by fgrossi           #+#    #+#             */
/*   Updated: 2022/05/04 15:17:08 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Incl/philo_B.h"

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
