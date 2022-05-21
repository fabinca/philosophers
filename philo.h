/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:46:21 by cfabian          ###   ########.fr       */
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

# define RED "\033[0;31m"
# define DEF "\033[0m"
# define DEAD 0
# define ALIVE 1
# define MAX_VAL 1
# define MIN_VAL 0
# define MAX_PHILO 200
# define MIN_MEALS 1
# define MIN_TIME 60

typedef struct s_data
{
	int				nb_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	bool			term;
	bool			err;
	int				philos_finished_nbm;
	bool			*fork_state;
	int64_t			start;
	pthread_mutex_t	print;
	pthread_mutex_t	check_term;
	pthread_mutex_t	enough_meals;
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
bool	safe_usleep(t_philo *philo, int64_t time);

//utils
int		ft_atoi_philo(const char *str, bool *err, int limit, bool type);
bool	ft_str_is_numeric(char *str);
int64_t	ft_gettimestamp(int64_t start);
int64_t	safe_print(t_philo *philo, char *message);

//forks
bool	check_fork(t_philo *philo, int fork);
void	put_down_fork(t_philo *philo, bool side);
bool	take_left_fork(t_philo *philo);
bool	take_right_fork(t_philo *philo);

//philo_action
bool	think(t_philo *philo);
bool	eat(t_philo *philo);
bool	philo_sleep(t_philo *philo);
bool	term(t_philo *philo);

//philo
void	*philo_thread(void *ptr);

#endif