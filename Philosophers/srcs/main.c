/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:38 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/28 13:51:02 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	threading(t_p *p);
static int	set_philo_n_forks(t_p *p);
static void	end_free(t_p *p);

/*----------------------------------------------------------------------------*/

int	main(int argc, char **argv)
{
	t_p	p;

/*---------------------------------parsing------------------------------------*/
	if (parsing(argc, argv, &p))
		return (perror("Invalid Arguments dude\n"), EXIT_FAILURE);

/*----------------------------init_philo_struct-------------------------------*/
	p.ph = ft_calloc(p.a.total, sizeof(t_philo));
	if (!p.ph)
		return (perror("Calloc fucked up bro\n"), EXIT_FAILURE);

/*------------------------------set_philo_n_forkc-----------------------------*/
	if (set_philo_n_forks(&p))
		return (perror("Init philo/forks FAILED\n"), free(p.ph), EXIT_FAILURE);

/*-----------------------------start_philos_threads---------------------------*/
	p.a.start_t = get_time();
	threading(&p);

/*------------------------------------end-------------------------------------*/
	end_free(&p);
	return (0);
}

static int	set_philo_n_forks(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
		if (init_philo(&p->ph[i], &p->a, i))
			return (1);
	if (init_forks(p))
		return (1);
	return (0);
}


static void	threading(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
		if (pthread_create(&p->ph[i].thread_id, NULL, &routine, &p))
			perror("Error during thread creation\n");
	i = -1;
	while (++i < p->a.total)
		if (pthread_join(p->ph[i].thread_id, NULL))
			perror("Error during thread joining\n");
}

static void	end_free(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
		pthread_mutex_destroy(&p->a.forks[i]);
	pthread_mutex_destroy(&p->a.write_mutex);
	pthread_mutex_destroy(&p->a.lock);
	i = -1;
	while (++i < p->a.total)
		pthread_mutex_destroy(&p->ph[i].lock);
	free(p->ph);
	free(p->a.forks);
}
