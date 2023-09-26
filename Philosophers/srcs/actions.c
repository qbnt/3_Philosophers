/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:29:26 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/26 14:57:17 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo);
static void	drop_forks(t_philo *philo);

/*----------------------------------------------------------------------------*/

void	message(char *str, t_philo *philo)
{
	unsigned long long	time;

	time = ;
	pthread_mutex_lock(&philo->pa->write_mutex);
	printf("%d: Philosopher %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->pa->write_mutex);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->pa->time_eat);
	philo->eating = 1;
	message(EATING, philo);
	philo->nb_eat ++;
	usleap(philo->pa->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->pa->time_eat);
	drop_forks(philo);
}

void	set_time(t_p *p)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE\n"));
	p->a.start_t = (int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_f);
	message(TAKE_FORKS, philo);
	pthread_mutex_lock(&philo->l_f);
	message(TAKE_FORKS, philo);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->r_f);
	pthread_mutex_unlock(&philo->l_f);
	message(SLEEPING, philo);
	usleap(philo->pa->sleep);
}
