/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:23:50 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/14 09:09:56 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/
void	*routine(void *philo_ptr)
{
	t_philo		*philo;
	pthread_t	t1984;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = get_time() + philo->death_t;
	if (pthread_create(&t1984, NULL, &supervisor, (void *)philo))
		return ((void *) 0);
	pthread_mutex_lock(&philo->pa->lock);
	while (philo->pa->dead == 0)
	{
		pthread_mutex_unlock(&philo->pa->lock);
		eat(philo);
		message(SLEEPING, philo);
		usleep(philo->sleep_t * 1000);
		message(THINKING, philo);
		pthread_mutex_lock(&philo->pa->lock);
	}
	pthread_mutex_unlock(&philo->pa->lock);
	if (pthread_join(t1984, NULL))
		return ((void *) 0);
	return ((void *) 0);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->pa->lock);
	while (philo->pa->dead == 0)
	{
		pthread_mutex_unlock(&philo->pa->lock);
		pthread_mutex_lock(&philo->pa->lock);
		if (get_time() > philo->time_to_die && philo->eating == 0)
		{
			pthread_mutex_unlock(&philo->pa->lock);
			message(DIED, philo);
			pthread_mutex_lock(&philo->pa->lock);
		}
		pthread_mutex_unlock(&philo->pa->lock);
		pthread_mutex_lock(&philo->pa->lock);
		if (philo->nb_eat == philo->pa->nb_meal)
		{
			pthread_mutex_unlock(&philo->pa->lock);
			pthread_mutex_lock(&philo->pa->lock);
			philo->pa->meal_philo_end ++;
			pthread_mutex_unlock(&philo->pa->lock);
			philo->nb_eat ++;
			pthread_mutex_lock(&philo->pa->lock);
		}
		pthread_mutex_unlock(&philo->pa->lock);
		pthread_mutex_lock(&philo->pa->lock);
	}
	pthread_mutex_unlock(&philo->pa->lock);
	return ((void *)0);
}

void	*check_meal(void *info_ptr)
{
	t_arg	*info;

	info = info_ptr;
	pthread_mutex_lock(&info->lock);
	while (!info->dead)
	{
		pthread_mutex_unlock(&info->lock);
		pthread_mutex_lock(&info->lock);
		if (info->meal_philo_end >= info->total)
			info->dead = 1;
	}
	pthread_mutex_unlock(&info->lock);
	return ((void *)0);
}
