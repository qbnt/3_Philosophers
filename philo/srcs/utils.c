/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:28 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/16 13:58:52 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*----------------------------------------------------------------------------*/

t_u_lli	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE\n"), -1);
	return ((tv.tv_sec * (t_u_lli)1000) + (tv.tv_usec / 1000));
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
		pthread_mutex_unlock(t1);
	if (t2)
		pthread_mutex_unlock(t1);
	if (t3)
		pthread_mutex_unlock(t1);
	if (t4)
		pthread_mutex_unlock(t1);
}
