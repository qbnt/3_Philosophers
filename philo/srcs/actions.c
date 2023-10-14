/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:29:26 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/14 09:15:45 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo);
static void	drop_forks(t_philo *philo);

/*----------------------------------------------------------------------------*/

void	message(char *str, t_philo *philo)
{
	U_LLI_T	time;

	pthread_mutex_lock(&philo->pa->write_mutex);
	pthread_mutex_lock(&philo->pa->lock);
	time = get_time() - philo->pa->start_t;
	pthread_mutex_unlock(&philo->pa->lock);
	pthread_mutex_lock(&philo->pa->lock);
	if (ft_strcmp(DIED, str) == 0 && philo->pa->dead == 0)
	{
		pthread_mutex_unlock(&philo->pa->lock);
		printf("%llu %d %s\n", time, philo->id, str);
		pthread_mutex_lock(&philo->pa->lock);
		philo->pa->dead = 1;
		pthread_mutex_unlock(&philo->pa->lock);
		pthread_mutex_lock(&philo->pa->lock);
	}
	pthread_mutex_unlock(&philo->pa->lock);
	pthread_mutex_lock(&philo->pa->lock);
	if (philo->pa->dead == 0)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->pa->lock);
	pthread_mutex_unlock(&philo->pa->write_mutex);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->eating = 1;
	philo->nb_eat ++;
	message(EATING, philo);
	pthread_mutex_lock(&philo->pa->lock);
	philo->time_to_die = get_time() + philo->death_t;
	pthread_mutex_unlock(&philo->pa->lock);
	usleep(philo->eat_t * 1000);
	philo->eating = 0;
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
	pthread_mutex_unlock(philo->r_f);
	pthread_mutex_unlock(philo->l_f);
}
