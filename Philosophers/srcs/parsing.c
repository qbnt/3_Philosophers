/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:27:08 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/26 13:49:02 by qbanet           ###   ########.fr       */
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
		p->a.die = (int)ft_atol(argv[2]);
		p->a.eat = (int)ft_atol(argv[3]);
		p->a.sleep = (int)ft_atol(argv[4]);
		if (argc == 5)
			p->a.m_eat = -1;
		else
			p->a.m_eat = (int)ft_atol(argv[5]);
		if (p->a.total < 1 || p->a.die < 1 || p->a.eat < 1 || p->a.sleep < 1)
			return (0);
		pthread_mutex_init(&p->a.write_mutex, NULL);
		pthread_mutex_init(&p->a.dead, NULL);
		pthread_mutex_init(&p->a.time_eat, NULL);
		pthread_mutex_init(&p->a.nb_p_end, NULL);
		return (1);
	}
	return (0);
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

void	init_philo(t_philo *philo, t_arg *arg, int id)
{
	philo->id = id;
	pthread_mutex_init(&philo->r_f, NULL);
	pthread_mutex_init(&philo->l_f, NULL);
	philo->pa = arg;
	philo->ms_eat = 0;
	philo->nb_eat = 0;
	philo->end = 0;
}