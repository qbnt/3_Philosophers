/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:52 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/26 14:44:38 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H

# include "philosophers.h"

/*parsing result*/
typedef struct s_arg
{
	int					total;
	int					die;
	int					eat;
	int					sleep;
	int					m_eat;
	long int			start_t;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		dead;
	pthread_mutex_t		time_eat;
	pthread_mutex_t		finish;
	int					nb_p_end;
}						t_arg;

/*struct du philo*/
typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_t			thread_death_id;
	pthread_mutex_t		*r_f;
	pthread_mutex_t		*l_f;
	t_arg				*pa;
	long int			ms_eat;
	unsigned int		nb_eat;
	int					eating;
	int					end;
}						t_philo;

/*struct a tout faire*/
typedef struct s_p
{
	t_philo				*ph;
	t_arg				a;
}						t_p;

#endif