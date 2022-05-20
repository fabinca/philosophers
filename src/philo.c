/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:27 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/20 13:53:27 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	get_forks(t_philo *philo)
{
	if (philo->number != 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}	
	if (philo->hand_fork[0] == 1 && philo->hand_fork[1] == 1)
		return (true);
	return (false);
	// if (ft_gettimestamp() - philo->last_food > \
	// philo->data_ptr->time_to_die - 50)
	// 	return (false);
	// put_down_needed_forks(philo);
	// return (false);
}

void	*philo_thread(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->last_food = philo->data_ptr->start;
	if (philo->data_ptr->nb_p % 2 == 0)
	{
		if (philo->number % 2 == 1)
			usleep(philo->data_ptr->time_to_eat * 1000 / 2);
	}
	else if (philo->number % 3 == 1)
		usleep(philo->data_ptr->time_to_eat * 1000 / 4);
	else if (philo->number % 3 == 2)
		usleep(philo->data_ptr->time_to_eat * 1000 / 2);
	while (!term(philo))
	{
		if (get_forks(philo))
		{
			eat(philo);
			philo_sleep(philo);
			think(philo, 1);
		}
	}
	return (NULL);
}
