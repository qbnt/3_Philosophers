/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:38 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/06 09:47:03 by qbanet           ###   ########.fr       */
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

	if (parsing(argc, argv, &p))
		return (perror("Invalid Arguments dude\n"), EXIT_FAILURE);
	p.ph = ft_calloc(p.a.total, sizeof(t_philo));
	if (!p.ph)
		return (perror("Calloc fucked up bro\n"), EXIT_FAILURE);
	if (set_philo_n_forks(&p))
		return (perror("Init philo/forks FAILED\n"), free(p.ph), EXIT_FAILURE);
	p.a.start_t = get_time();
	threading(&p);
	end_free(&p);
	return (0);
}

static int	set_philo_n_forks(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
		if (init_philo(&p->ph[i], &p->a, i + 1))
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
	{
		if (pthread_create(&p->ph[i].thread_id, NULL, &routine, &p->ph[i]))
			perror("Error during thread creation\n");
		usleep(10);
	}
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
