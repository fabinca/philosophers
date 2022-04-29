/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:27 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/29 15:02:02 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (philo->number < philo->left)
	{
		take_fork(philo, philo->number);
		take_fork(philo, philo->left);
	}
	else
	{
		take_fork(philo, philo->left);
		take_fork(philo, philo->number);
	}
	return (1);
}

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
		if (philo->data_ptr->nb_p == philo->data_ptr->philos_finished_nbm)
			break ;
		if (can_take_forks(philo))
		{
			eat(philo);
			if (philo->data_ptr->nb_p == philo->data_ptr->philos_finished_nbm)
				break ;
			philo_sleep(philo);
			if (philo->data_ptr->nb_p == philo->data_ptr->philos_finished_nbm)
				break ;
			think(philo);
		}
	}
	return (NULL);
}
