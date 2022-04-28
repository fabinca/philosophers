/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/28 15:39:12 by cfabian          ###   ########.fr       */
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

typedef struct s_philo
{
	int				number;
	int				status; /*0:dead 1:eating 2:else */
	int64_t			last_food;
	int				nb_meals;
	bool			fork_sema_right;
	bool			fork_sema_left;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals; //-10 if unspecified
	bool			dead;
	pthread_mutex_t	check_forks;
	bool			*fork_semaphores;
}					t_data;

int		ft_atoi(const char *str);
int64_t	get_timestamp(void);
void	free_all(pthread_t *tid, t_data ptr);

#endif