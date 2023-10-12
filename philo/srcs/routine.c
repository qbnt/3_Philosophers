/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:23:50 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/12 09:16:06 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/
void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	U_LLI_T	dodo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->pa->lock);
	dodo = philo->pa->sleep_t;
	pthread_mutex_unlock(&philo->pa->lock);
	pthread_mutex_lock(&philo->pa->lock);
	philo->time_to_die = get_time() + philo->pa->death_t;
	pthread_mutex_unlock(&philo->pa->lock);
	if (pthread_create(&philo->thread_id, NULL, &supervisor, (void *)philo))
		return ((void *) 0);
	pthread_mutex_lock(&philo->pa->lock);
	while (philo->pa->dead == 0)
	{
		pthread_mutex_unlock(&philo->pa->lock);
		eat(philo);
		message(SLEEPING, philo);
		usleep(dodo * 1000);
		message(THINKING, philo);
		pthread_mutex_lock(&philo->pa->lock);
	}
	pthread_mutex_unlock(&philo->pa->lock);
	unlock_mutex_all(&philo->lock, &philo->pa->lock, &philo->pa->write_mutex,
		NULL);
	unlock_all_forks(philo->pa);
	return (philo_ptr);
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
			philo->nb_eat ++;
		}
		pthread_mutex_unlock(&philo->pa->lock);
		pthread_mutex_lock(&philo->pa->lock);
	}
	pthread_mutex_unlock(&philo->pa->lock);
	unlock_mutex_all(&philo->lock, &philo->pa->lock, &philo->pa->write_mutex,
		NULL);
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
	unlock_mutex_all(NULL, &info->lock, &info->write_mutex,
		NULL);
	return ((void *)0);
}
