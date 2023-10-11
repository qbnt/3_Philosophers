/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:23:50 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/11 14:51:04 by qbanet           ###   ########.fr       */
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
	philo->time_to_die = get_time() + philo->pa->death_t;
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
	return ((void *)0);
}

void	*check_meal(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	pthread_mutex_lock(&philo->pa->lock);
	while (!philo->pa->dead)
	{
		pthread_mutex_unlock(&philo->pa->lock);
		pthread_mutex_lock(&philo->pa->lock);
		if (philo->pa->meal_philo_end >= philo->pa->total)
			philo->pa->dead = 1;
	}
	pthread_mutex_unlock(&philo->pa->lock);
	return ((void *)0);
}
