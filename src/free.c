/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:09 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:48:18 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(pthread_t *tid, t_data data, t_philo *philos)
{
	if (tid)
		free(tid);
	if (philos)
		free(philos);
	if (data.fork_state)
		free(data.fork_state);
	if (data.f_mutex)
		free(data.f_mutex);
}
