/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:52 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/26 16:38:10 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H

# include "philosophers.h"

/*parsing result*/
typedef struct s_arg
{
	int					total;
	int					nb_meal;
	int					death_t;
	int					eat_t;
	int					sleep_t;
	long int			start_t;
	int					dead;
	int					end;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write_mutex;
}						t_arg;

/*struct du philo*/
typedef struct s_philo
{
	int					id;
	t_arg				*pa;
	pthread_t			thread_id;
	unsigned int		nb_eat;
	int					eating;
	int					dying_time;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_f;
	pthread_mutex_t		*l_f;
}						t_philo;

/*struct a tout faire*/
typedef struct s_p
{
	t_philo				*ph;
	t_arg				a;
}						t_p;

#endif