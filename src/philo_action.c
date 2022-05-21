/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 01:02:08 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	think(t_philo *philo)
{
	if (safe_print(philo, "is thinking") > 1)
		return (ALIVE);
	return (DEAD);
}

bool	eat(t_philo *philo)
{
	const int64_t	now = safe_print(philo, "is eating");

	if (now == -1)
		return (DEAD);
	philo->nb_meals += 1;
	if (philo->nb_meals == philo->data_ptr->nb_meals)
	{
		pthread_mutex_lock(&philo->data_ptr->enough_meals);
		philo->data_ptr->philos_finished_nbm += 1;
		if (philo->data_ptr->philos_finished_nbm == philo->data_ptr->nb_p)
		{
			pthread_mutex_unlock(&philo->data_ptr->enough_meals);
			pthread_mutex_lock(&philo->data_ptr->check_term);
			philo->data_ptr->term = 1;
			pthread_mutex_unlock(&philo->data_ptr->check_term);
		}
		else
			pthread_mutex_unlock(&philo->data_ptr->enough_meals);
	}
	philo->last_food = now;
	if (safe_usleep(philo, now + philo->data_ptr->time_to_eat) == DEAD)
		return (DEAD);
	put_down_fork(philo, 0);
	put_down_fork(philo, 1);
	return (ALIVE);
}

bool	philo_sleep(t_philo *philo)
{
	int64_t	now;

	now = safe_print(philo, "is sleeping");
	if (safe_usleep(philo, now + philo->data_ptr->time_to_sleep) == DEAD)
		return (DEAD);
	return (ALIVE);
}

bool	term(t_philo *philo)
{
	int64_t	now;

	pthread_mutex_lock(&philo->data_ptr->check_term);
	if (philo->data_ptr->term > 0)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (1);
	}
	now = ft_gettimestamp(philo->data_ptr->start);
	if (now - philo->last_food < philo->data_ptr->time_to_die)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (0);
	}
	philo->data_ptr->term += 1;
	pthread_mutex_unlock(&philo->data_ptr->check_term);
	pthread_mutex_lock(&philo->data_ptr->print);
	printf("%i philosopher %i has died.\n", \
	(int)ft_gettimestamp(philo->data_ptr->start), philo->number + 1);
	pthread_mutex_unlock(&philo->data_ptr->print);
	return (1);
}
