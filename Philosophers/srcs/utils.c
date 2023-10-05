/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:28 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/05 11:13:58 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_bzero(void *s, size_t n);

/*----------------------------------------------------------------------------*/

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE\n"), -1);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
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

int	ft_strcmp(char const *s1, char const *s2)
{
	while ((unsigned char)*s1 == (unsigned char)*s2 && *s1)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
