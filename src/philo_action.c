/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/29 15:13:29 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo, int fork)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[fork]);
	printf("%li philosopher %i has taken a fork.\n", now, philo->number + 1);
}

void	think(t_philo *philo)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	printf("%li philosopher %i is thinking.\n", now, philo->number + 1);
}

void	eat(t_philo *philo)
{
	int64_t	now;

	now = get_timestamp();
	philo->nb_meals += 1;
	printf("%li philosopher %i is eating. (%i)\n", \
	now, philo->number + 1, philo->nb_meals);
	if (philo->nb_meals == philo->data_ptr->nb_meals)
	{
		pthread_mutex_lock(&philo->data_ptr->incr_philos_finished);
		philo->data_ptr->philos_finished_nbm += 1;
		pthread_mutex_unlock(&philo->data_ptr->incr_philos_finished);
	}
	usleep(philo->data_ptr->time_to_sleep * 1000);
	philo->last_food = now;
	philo->data_ptr->fork_semaphores[philo->left] = 1;
	philo->data_ptr->fork_semaphores[philo->number] = 1;
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
}

void	philo_sleep(t_philo *philo)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	printf("%li philosopher %i is sleeping.\n", now, philo->number + 1);
	if (now - philo->last_food + philo->data_ptr->time_to_sleep * 1000 < \
		philo->data_ptr->time_to_die * 1000)
		usleep(philo->data_ptr->time_to_sleep * 1000);
	else
		usleep((philo->data_ptr->time_to_die * 1000 - \
		(now - philo->last_food)));
}

bool	dead(t_philo *philo, int64_t now)
{
	pthread_mutex_lock(&philo->data_ptr->check_dead);
	if (philo->data_ptr->dead == 1)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_dead);
		return (1);
	}
	if (now - philo->last_food < philo->data_ptr->time_to_die)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_dead);
		return (0);
	}
	philo->data_ptr->dead = 1;
	pthread_mutex_unlock(&philo->data_ptr->check_dead);
	printf("%li philosopher %i died.\n", now, philo->number + 1);
	return (1);
}
