/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:45:05 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/28 13:20:53 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/

int	init_philo(t_philo *philo, t_arg *arg, int id)
{
	philo->id = id;
	philo->pa = arg;
	philo->nb_eat = 0;
	philo->eating = 0;
	philo->dying_time = 0;
	return (0);
}

int	init_forks(t_p *p)
{
	int	i;

	i = -1;
	p->a.forks = ft_calloc(p->a.total, sizeof(pthread_mutex_t));
	while (++i < p->a.total)
	{
		if (pthread_mutex_init(&p->a.forks[i], NULL))
			return (1);
	}
	p->ph[0].r_f = &p->a.forks[0];
	p->ph[0].l_f = &p->a.forks[p->a.total - 1];
	i = 1;
	while (i < p->a.total)
	{
		p->ph[i].r_f = &p->a.forks[i];
		p->ph[i].l_f = &p->a.forks[i - 1];
		i ++;
	}
	return (0);
}
