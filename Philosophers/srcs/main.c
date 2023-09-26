/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:38 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/26 16:37:35 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	threading(t_p *p);

/*----------------------------------------------------------------------------*/

int	main(int argc, char **argv)
{
	t_p	p;

	if (!parsing(argc, argv, &p))
		return (perror("Invalid Arguments dude\n"), EXIT_FAILURE);
	set_time(&p);
	p.ph = malloc(p.a.total * sizeof(t_philo));
	if (!p.ph)
		return (perror("Malloc fucked up bro\n"), EXIT_FAILURE);
	set_philo_n_forks(&p);
	threading(&p);
	free(p.ph);
	return (0);
}

static void	set_philo_n_forks(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->a.total)
	{
		init_philo(&p->ph[i], &p->a, i);
		i ++;
	}
	init_forkc(p);
}

static void	threading(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->a.total)
	{
		if (pthread_create(&p->ph[i].thread_id, NULL, &routine, &p))
			perror("Error during thread creation\n");
		i ++;
	}
	i = 0;
	while (i < p->a.total)
	{
		if (pthread_join(p->ph[i].thread_id, NULL))
			perror("Error during thread joining\n");
		i ++;
	}
}
