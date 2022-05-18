/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 16:37:20 by cfabian          ###   ########.fr       */
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
	bool			term;
	pthread_mutex_t	incr_philos_finished;
	pthread_mutex_t	check_term;
	int				philos_finished_nbm;
	bool			*fork_state;
	pthread_mutex_t	*f_mutex;
}					t_data;

typedef struct s_philo
{
	int				number;
	int				left;
	bool			hand_fork[2];
	int64_t			last_food;
	int				nb_meals;
	t_data			*data_ptr;
}					t_philo;

//free
void	free_all(pthread_t *tid, t_data data, t_philo *philos);
//utils
int		ft_atoi(const char *str);
bool	ft_str_is_numeric(char *str);
int64_t	ft_gettimestamp(void);
//main
//philo_action
void	put_down_right_fork(t_philo *philo);
void	put_down_left_fork(t_philo *philo);
void	take_left_fork(t_philo *philo);
void	take_right_fork(t_philo *philo);
void	think(t_philo *philo, int64_t time);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
bool	term(t_philo *philo);

//philo
void	*philo_thread(void *ptr);

#endif