/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:28 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/28 12:55:09 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_bzero(void *s, size_t n);

/*----------------------------------------------------------------------------*/

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE\n"), 0);
	time = ((tv.tv_sec * 1000000) + (tv.tv_usec));
	return (time);
}

int	ft_usleep(suseconds_t time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	test;

	if (size != 0 && nmemb != 0)
	{
		test = size * nmemb;
		if ((test / nmemb != size) || (test / size != nmemb))
			return (NULL);
	}
	ret = (void *)malloc(size * nmemb);
	if (!ret)
		return (NULL);
	ft_bzero(ret, size * nmemb);
	return (ret);
}

static void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = '\0';
}