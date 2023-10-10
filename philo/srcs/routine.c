/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:23:50 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/10 14:36:52 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = get_time() + philo->pa->death_t;
	if (pthread_create(&philo->thread_id, NULL, &supervisor, (void *)philo))
		return ((void *) 0);
	while (philo->pa->dead == 0)
	{
		eat(philo);
		message(SLEEPING, philo);
		usleep(philo->pa->sleep_t * 1000);
		message(THINKING, philo);
	}
	return (philo_ptr);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->pa->dead == 0)
	{
		if (get_time() > philo->time_to_die && philo->eating == 0)
			message(DIED, philo);
		if (philo->nb_eat == philo->pa->nb_meal)
		{
			pthread_mutex_lock(&philo->pa->lock);
			philo->pa->meal_philo_end ++;
			philo->nb_eat ++;
			pthread_mutex_unlock(&philo->pa->lock);
		}
	}
	return ((void *)0);
}

void	*check_meal(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	while (!philo->pa->dead)
	{
		pthread_mutex_lock(&philo->pa->lock);
		if (philo->pa->meal_philo_end >= philo->pa->total)
			philo->pa->dead = 1;
		pthread_mutex_unlock(&philo->pa->lock);
	}
	return ((void *)0);
}
