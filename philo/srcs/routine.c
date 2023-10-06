/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:23:50 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/06 11:24:26 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->pa->death_t + get_time();
	if (pthread_create(&philo->thread_id, NULL, &supervisor, (void *)philo))
		return ((void *) 0);
	while (!philo->pa->dead)
	{
		eat(philo);
		message(THINKING, philo);
		printf("-----------------------------------------\n");
	}
	return (philo_ptr);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (!philo->pa->dead)
	{
		if (get_time() >= philo->time_to_die && !philo->eating)
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
		if (philo->pa->total == philo->pa->meal_philo_end)
		{
			pthread_mutex_lock(&philo->pa->lock);
			printf("oui\n");
			pthread_mutex_unlock(&philo->pa->lock);
		}
	}
	return ((void *)0);
}
