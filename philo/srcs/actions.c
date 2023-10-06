/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:29:26 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/05 11:15:43 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo);
static void	drop_forks(t_philo *philo);

/*----------------------------------------------------------------------------*/

void	message(char *str, t_philo *philo)
{
	u_int64_t	time;

	time = get_time() - philo->pa->start_t;
	pthread_mutex_lock(&philo->pa->write_mutex);
	if (ft_strcmp(DIED, str) == 0 && philo->pa->dead == 0)
	{
		printf("%li:	Philosopher %d	%s\n", time, philo->id, str);
		philo->pa->dead = 1;
	}
	if (!philo->pa->dead)
		printf("%li:	Philosopher %d	%s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->pa->write_mutex);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->pa->lock);
	philo->eating = 1;
	message(EATING, philo);
	philo->nb_eat ++;
	usleep(philo->pa->eat_t);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->pa->lock);
	drop_forks(philo);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_f);
	message(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->r_f);
	message(TAKE_FORKS, philo);
}


static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
	message(SLEEPING, philo);
	usleep(philo->pa->sleep_t);
}
