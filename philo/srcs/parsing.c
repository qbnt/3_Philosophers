/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:27:08 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/16 13:59:00 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	dstr_is_all_num(char **argv, int i, int j);
static long	ft_atol(const char *str);

/*----------------------------------------------------------------------------*/

int	parsing(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && dstr_is_all_num(argv, 0, 1))
	{
		p->a.total = (int)ft_atol(argv[1]);
		p->a.death_t = (t_u_lli)ft_atol(argv[2]);
		p->a.eat_t = (t_u_lli)ft_atol(argv[3]);
		p->a.sleep_t = (t_u_lli)ft_atol(argv[4]);
		if (argc != 6)
			p->a.nb_meal = -1;
		else
			p->a.nb_meal = (int)ft_atol(argv[5]);
		if (p->a.total < 1 || p->a.death_t < 1 || p->a.eat_t < 1
			|| p->a.sleep_t < 1)
			return (1);
		p->a.dead = 0;
		p->a.meal_philo_end = 0;
		pthread_mutex_init(&p->a.lock, NULL);
		pthread_mutex_init(&p->a.write_mutex, NULL);
		return (0);
	}
	return (1);
}

static int	dstr_is_all_num(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
			i ++;
		}
		if (ft_atol(argv[j]) > _INT_MAX)
			return (0);
		j ++;
		i = 0;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while ((*str >= '\a' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str ++;
	while (*str >= '0' && *str <= '9')
		nbr = (((long long)*str++ - 48) + nbr * 10);
	return (nbr * sign);
}
