/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/28 17:01:41 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philo philo)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	printf("%i philosopher %i is thinking.\n", now, philo.number);
}

void	eat(t_philo philo)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	printf("%i philosopher %i is eating.\n", now, philo.number);
	usleep(philo.data_ptr->time_to_sleep * 100);
	philo.last_food = now;
}

void	sleep(t_philo philo)
{
	int64_t	now;

	now = get_timestamp();
	if (dead(philo, now))
		return ;
	printf("%i philosopher %i is eating.\n", now, philo.number);
	if (now - philo.last_food + philo.data_ptr->time_to_sleep < \
		philo.data_ptr->time_to_die)
		usleep(philo.data_ptr->time_to_sleep * 100);
	else
		usleep((philo.data_ptr->time_to_die - (now - philo.last_food)) * 100);
}

bool	dead(t_philo philo, int64_t now)
{
	if (philo.data_ptr->dead == 1)
		return (1);
	if (now - philo.last_food < philo.data_ptr->time_to_die)
		return (0);
	printf("%i philosopher %i died.\n", now, philo.number);
	return (1);
}

