/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/21 13:13:43 by cfabian          ###   ########.fr       */
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

typedef struct s_data
{
	int				nb_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	bool			term;
	int				philos_finished_nbm;
	bool			*fork_state;
	int64_t			start;
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

//utils
int		ft_atoi(const char *str);
bool	ft_str_is_numeric(char *str);
int64_t	ft_gettimestamp(int64_t start);

//forks
bool	check_fork(t_philo *philo, int fork);
void	put_down_needed_forks(t_philo *philo);
void	put_down_fork(t_philo *philo, bool side);
bool	take_left_fork(t_philo *philo);
bool	take_right_fork(t_philo *philo);

//philo_action
void	print_message(t_philo *philo, char *message);
void	think(t_philo *philo, int64_t time);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
bool	term(t_philo *philo);

//philo
void	*philo_thread(void *ptr);

#endif