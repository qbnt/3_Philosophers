/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:38 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/14 09:17:55 by qbanet           ###   ########.fr       */
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

	if (argc < 5 || argc > 6)
		return (0);
	if (parsing(argc, argv, &p))
		return (perror("Invalid Arguments dude\n"), EXIT_FAILURE);
	p.ph = malloc(p.a.total * sizeof(t_philo) + 1);
	if (!p.ph)
		return (perror("Calloc fucked up bro\n"), EXIT_FAILURE);
	if (set_philo_n_forks(&p))
		return (perror("Init philo/forks FAILED\n"), free(p.ph), EXIT_FAILURE);
	threading(&p);
	end_free(&p);
	return (0);
}

static int	set_philo_n_forks(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
	{
		if (init_philo(&p->ph[i], &p->a, i + 1))
			return (1);
	}
	if (init_forks(p))
		return (1);
	return (0);
}

static void	threading(t_p *p)
{
	int			i;
	pthread_t	t0;

	i = -1;
	t0 = 0;
	if (p->a.nb_meal > 0)
		if (pthread_create(&t0, NULL, &check_meal, &p->a))
			perror("Error during thread creation\n");
	p->a.start_t = get_time();
	while (++i < p->a.total)
		if (pthread_create(&p->ph[i].thread_id, NULL, &routine, &p->ph[i]))
			perror("Error during thread creation\n");
	i = -1;
	while (++i < p->a.total)
		if (pthread_join(p->ph[i].thread_id, NULL))
			perror("Error during thread joining\n");
	if (t0)
		if (pthread_join(t0, NULL))
			perror("Error during thread joining\n");
}

static void	end_free(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
	{
		pthread_mutex_lock(&p->a.forks[i]);
		pthread_mutex_unlock(&p->a.forks[i]);
		pthread_mutex_destroy(&p->a.forks[i]);
	}
	pthread_mutex_destroy(&p->a.lock);
	pthread_mutex_destroy(&p->a.write_mutex);
	free(p->a.forks);
	free(p->ph);
}
