/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:27 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:41:03 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	get_forks(t_philo *philo)
{
	if (ft_gettimestamp(philo->data_ptr->start) - philo->last_food \
	>= philo->data_ptr->time_to_eat)
	{
		while (!philo->hand_fork[0] || !philo->hand_fork[1])
		{
			take_left_fork(philo);
			take_right_fork(philo);
			if (term(philo))
				return (0);
		}
	}
	if (philo->number % 2 != 0)
	{
		if (take_left_fork(philo))
			take_right_fork(philo);
	}
	else
	{
		if (take_right_fork(philo))
			take_left_fork(philo);
	}	
	if (philo->hand_fork[0] == 1 && philo->hand_fork[1] == 1)
		return (true);
	return (false);
}

static void	philo_start(t_philo *philo)
{
	if (philo->data_ptr->time_to_eat >= philo->data_ptr->time_to_die)
		return ;
	if (philo->data_ptr->nb_p % 2 == 0)
	{
		if (philo->number % 2 == 1)
			usleep(philo->data_ptr->time_to_eat * 1000 / 2);
	}
	else if (philo->number % 3 == 1)
		usleep(philo->data_ptr->time_to_eat * 1000 / 4);
	else if (philo->number % 3 == 2)
		usleep(philo->data_ptr->time_to_eat * 1000 / 2);
}

void	*philo_thread(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->last_food = philo->data_ptr->start;
	philo_start(philo);
	while (true)
	{
		if (get_forks(philo))
		{
			if (!eat(philo))
				break ;
			if (!philo_sleep(philo))
				break ;
			if (!think(philo))
				break ;
		}
		else if (term(philo))
			break ;
	}
	return (NULL);
}
