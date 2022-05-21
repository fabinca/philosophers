/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:28:22 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/21 16:08:23 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

#define TIME_STEPS 100

bool	safe_usleep(t_philo *philo, int64_t time)
{
	while (time > TIME_STEPS * 1000)
	{
		usleep(TIME_STEPS * 1000);
		time = time - TIME_STEPS * 1000;
		if (term(philo))
			return (1);
	}
	usleep(time);
	return (0);
}
