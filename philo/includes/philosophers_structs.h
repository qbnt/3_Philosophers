/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:52 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/11 14:30:08 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H

# include "philosophers.h"

# define U_LLI_T	unsigned long long int

/*parsing result*/
typedef struct s_arg
{
	int					total;
	int					nb_meal;
	int					meal_philo_end;
	U_LLI_T				death_t;
	U_LLI_T				eat_t;
	U_LLI_T				sleep_t;
	U_LLI_T				start_t;
	int					dead;
	int					end;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write_mutex;
}						t_arg;

/*struct du philo*/
typedef struct s_philo
{
	t_arg				*pa;
	pthread_t			thread_id;
	int					id;
	int					nb_eat;
	int					eating;
	U_LLI_T				time_to_die;
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