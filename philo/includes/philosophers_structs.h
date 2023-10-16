/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:52 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/16 14:03:24 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H

typedef unsigned long long int	t_u_lli;

/*parsing result*/
typedef struct s_arg
{
	int					total;
	int					nb_meal;
	int					meal_philo_end;
	int					dead;
	t_u_lli				death_t;
	t_u_lli				eat_t;
	t_u_lli				sleep_t;
	t_u_lli				start_t;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write_mutex;
}						t_arg;

/*struct du philo*/
typedef struct s_philo
{
	t_arg				*pa;
	pthread_t			thread_id;
	pthread_mutex_t		lock;
	int					id;
	int					nb_eat;
	int					eating;
	t_u_lli				death_t;
	t_u_lli				eat_t;
	t_u_lli				sleep_t;
	t_u_lli				time_to_die;
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
