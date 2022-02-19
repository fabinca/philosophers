/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/19 12:38:29 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				number;
	int				status; /*0:dead 1:eating 2:else */
	int				last_food;
	int				nb_meals;
	pthread_mutex_t	*fork;
	struct s_philo	*left;
	struct s_philo	*right;
}					t_philo;

typedef struct s_data
{
	int				number;
	t_philo			*philos;
	int				nb_of_philos;
	int				dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	pthread_mutex_t	*forks;
}					t_data;

int		ft_atoi(const char *str);
void	free_all(pthread_t *tid, t_data ptr);

#endif