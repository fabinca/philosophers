/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/19 11:28:47 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(int num, char *message)
{
	printf("%li philosopher %i %s.\n", ft_gettimestamp(), num + 1, message);
}

void	think(t_philo *philo, int64_t time)
{
	if (term(philo))
		return ;
	print_message(philo->number, "is thinking");
	usleep(time);
}

void	eat(t_philo *philo)
{
	int64_t	now;

	if (term(philo))
		return ;
	print_message(philo->number, "is eating");
	philo->nb_meals += 1;
	now = ft_gettimestamp();
	if (philo->nb_meals == philo->data_ptr->nb_meals)
	{
		philo->data_ptr->philos_finished_nbm += 1;
		if (philo->data_ptr->philos_finished_nbm == philo->data_ptr->nb_p)
			philo->data_ptr->term += 1;
	}
	usleep(philo->data_ptr->time_to_sleep * 1000 -(ft_gettimestamp() - now));
	philo->last_food = now;
	put_down_left_fork(philo);
	put_down_right_fork(philo);
}

void	philo_sleep(t_philo *philo)
{
	int64_t	now;

	if (term(philo))
		return ;
	print_message(philo->number, "is sleeping");
	now = ft_gettimestamp();
	if (now - philo->last_food + philo->data_ptr->time_to_sleep * 1000 < \
		philo->data_ptr->time_to_die * 1000)
		usleep(philo->data_ptr->time_to_sleep * 1000);
	else
		usleep((philo->data_ptr->time_to_die * 1000 - \
		(now - philo->last_food)));
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
	now = ft_gettimestamp();
	if (now - philo->last_food < philo->data_ptr->time_to_die)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->check_term);
	print_message(philo->number, "died");
	philo->data_ptr->term += 1;
	return (1);
}
