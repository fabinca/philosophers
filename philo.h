/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/29 14:19:15 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_data
{
	int				nb_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals; //-10 if unspecified
	bool			dead;
	pthread_mutex_t	check_mutex;
	bool			*fork_semaphores;
	pthread_mutex_t	*f_mutex;
}					t_data;

typedef struct s_philo
{
	int				number;
	int				left;
	int64_t			last_food;
	int				nb_meals;
	t_data			*data_ptr;
}					t_philo;

int		ft_atoi(const char *str);
int		ft_str_is_numeric(char *str);
int64_t	get_timestamp(void);
void	*philo_thread(void *ptr);
bool	can_take_forks(t_philo *philo);
void	take_fork(t_philo *philo, int fork);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
bool	dead(t_philo *philo, int64_t now);
void	free_all(pthread_t *tid, t_data ptr);

#endif