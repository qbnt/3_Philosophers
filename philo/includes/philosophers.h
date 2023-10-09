/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:55:34 by qbanet            #+#    #+#             */
/*   Updated: 2023/10/09 15:12:36 by qbanet           ###   ########.fr       */
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
# define _INT_MIN	-2147483648
# define _INT_MAX	2147483647
# define _UINT_MAX	4294967295
# define U_LLI_T	unsigned long long int

# define TAKE_FORKS	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

/*----fonctions----*/


/*parsing.c*/
int			parsing(int argc, char **argv, t_p *p);
int			init_philo(t_philo *philo, t_arg *arg, int id);
int			init_forks(t_p *p);
/*routine.c*/
void		*routine(void *philo);
void		*supervisor(void *philo_ptr);

/*actions.c*/
void		message(char *str, t_philo *philo);
void		eat(t_philo *philo);

/*utils.c*/
U_LLI_T		get_time(void);
int			ft_usleep(U_LLI_T time);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strcmp(char const *s1, char const *s2);

#endif