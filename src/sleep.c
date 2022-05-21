/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:28:22 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:50:14 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

#define TIME_STEPS 100

bool	safe_usleep(t_philo *philo, int64_t end)
{
	bool	status;

	if (end > philo->last_food + philo->data_ptr->time_to_die)
	{
		end = philo->last_food + philo->data_ptr->time_to_die;
		status = DEAD;
	}
	else
		status = ALIVE;
	while (end < ft_gettimestamp(philo->data_ptr->start) - TIME_STEPS)
	{
		usleep(TIME_STEPS * 1000);
		if (term(philo))
			return (DEAD);
	}
	usleep((end - ft_gettimestamp(philo->data_ptr->start)) * 1000);
	return (status);
}
