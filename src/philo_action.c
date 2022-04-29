/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/28 18:59:41 by cfabian          ###   ########.fr       */
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
	printf("%li philosopher %i has taken a fork.\n", now, philo->number);
}

bool	can_take_forks(t_philo *philo)
{
	bool	take_forks;

	take_forks = 0;
	pthread_mutex_lock(&philo->data_ptr->check_mutex);
	if (philo->data_ptr->fork_semaphores[philo->left] == 1 && \
	philo->data_ptr->fork_semaphores[philo->number] == 1)
	{
		take_forks = 1;
		philo->data_ptr->fork_semaphores[philo->left] = 0;
		philo->data_ptr->fork_semaphores[philo->number] = 0;
	}
	pthread_mutex_unlock(&philo->data_ptr->check_mutex);
	if (take_forks == 0)
		return (0);
	take_fork(philo, philo->number);
	take_fork(philo, philo->left);
	return (1);
}

void	think(t_philo *philo)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	printf("%li philosopher %i is thinking.\n", now, philo->number);
}

void	eat(t_philo *philo)
{
	int64_t	now;

	now = get_timestamp();
	philo->nb_meals += 1;
	printf("%li philosopher %i is eating. (nb %i)\n", now, philo->number, philo->nb_meals);
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
	printf("%li philosopher %i is sleeping.\n", now, philo->number);
	if (now - philo->last_food + philo->data_ptr->time_to_sleep * 1000 < \
		philo->data_ptr->time_to_die * 1000)
		usleep(philo->data_ptr->time_to_sleep * 1000);
	else
		usleep((philo->data_ptr->time_to_die * 1000 - (now - philo->last_food)));
}

bool	dead(t_philo *philo, int64_t now)
{
	if (philo->data_ptr->dead == 1)
		return (1);
	if (now - philo->last_food < philo->data_ptr->time_to_die)
		return (0);
	philo->data_ptr->dead = 1;
	printf("%li philosopher %i died.\n", now, philo->number);
	return (1);
}

