/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:27 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/28 17:43:11 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_thread(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->last_food = get_timestamp();
	if (philo->number != 0)
		think(philo);
	usleep(philo->number);
	while (!dead(philo, get_timestamp()))
	{
		if (can_take_forks(philo))
		{
			eat(philo);
			philo_sleep(philo);
			think(philo);
		}
	}
	return (NULL);
}
