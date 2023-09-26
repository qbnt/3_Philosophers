/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:34 by qbanet            #+#    #+#             */
/*   Updated: 2023/09/26 16:39:13 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*----libraries----*/
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*structures*/
# include "philosophers_structs.h"

/*defines*/
# define _INT_MIN -2147483648
# define _INT_MAX 2147483647
# define _UINT_MAX 4294967295

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

/*----fonctions----*/


/*parsing.c*/
int		parsing(int argc, char **argv, t_p *p);
void	init_philo(t_philo *philo, t_arg *arg, int id);
void	init_forks(t_p *p);

/*routine.c*/
void	*routine(void *arg);

/*actions.c*/
void	message(char *str, t_philo *philo);
void	eat(t_philo *philo);
void	get_time(t_p *p);

#endif