/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/17 16:08:30 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_data
{
	int	nb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	nb_meals;
}		t_data;

typedef struct s_philo
{
	int				number;
	int				time_to_die;
	pthread_mutex_t	*nb_fork;
	pthread_mutex_t	*fork;
}					t_philo;

#endif