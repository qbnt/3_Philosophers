/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:28 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/12 08:59:08 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/

U_LLI_T	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE\n"), -1);
	return ((tv.tv_sec * (U_LLI_T)1000) + (tv.tv_usec / 1000));
}

int	ft_strcmp(char const *s1, char const *s2)
{
	while ((unsigned char)*s1 == (unsigned char)*s2 && *s1)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	unlock_mutex_all(pthread_mutex_t *t1, pthread_mutex_t *t2,
	pthread_mutex_t *t3, pthread_mutex_t *t4)
{
	if (t1)
	{
		pthread_mutex_lock(t1);
		pthread_mutex_unlock(t1);
	}
	if (t2)
	{
		pthread_mutex_lock(t2);
		pthread_mutex_unlock(t2);
	}
	if (t3)
	{
		pthread_mutex_lock(t3);
		pthread_mutex_unlock(t3);
	}
	if (t4)
	{
		pthread_mutex_lock(t4);
		pthread_mutex_unlock(t4);
	}
}

void	unlock_all_forks(t_arg *args)
{
	int				nb_forks;
	pthread_mutex_t	oui;
	int				i;

	if (pthread_mutex_init(&oui, NULL))
		return ((void) 0);
	pthread_mutex_lock(&oui);
	nb_forks = args->total;
	pthread_mutex_unlock(&oui);
	i = -1;
	while (++i < nb_forks)
	{
		pthread_mutex_lock(&args->forks[i]);
		pthread_mutex_unlock(&args->forks[i]);
	}
}
