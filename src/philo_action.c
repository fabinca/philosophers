/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             *//*   Updated: 2022/05/20 11:38:43 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(t_philo *philo, char *message)
{
	printf("%lli philosopher %i %s.\n", ft_gettimestamp(philo->data_ptr->start), philo->number + 1, message);
}

void	think(t_philo *philo, int64_t time)
{
	if (term(philo))
		return ;
	print_message(philo, "is thinking");
	usleep(time);
}

void	eat(t_philo *philo)
{
	int64_t	now;

	if (term(philo))
		return ;
	print_message(philo, "is eating");
	philo->nb_meals += 1;
	now = ft_gettimestamp(philo->data_ptr->start);
	if (philo->nb_meals == philo->data_ptr->nb_meals)
	{
		pthread_mutex_lock(&philo->data_ptr->enough_meals);
		philo->data_ptr->philos_finished_nbm += 1;
		if (philo->data_ptr->philos_finished_nbm == philo->data_ptr->nb_p)
		{
			pthread_mutex_unlock(&philo->data_ptr->enough_meals);
			pthread_mutex_lock(&philo->data_ptr->check_term);
			philo->data_ptr->term += 1;
			pthread_mutex_unlock(&philo->data_ptr->check_term);
		}
		else
			pthread_mutex_unlock(&philo->data_ptr->enough_meals);
	}
	usleep(philo->data_ptr->time_to_sleep * 1000 -(ft_gettimestamp(philo->data_ptr->start) - now));
	philo->last_food = now;
	put_down_fork(philo, 0);
	put_down_fork(philo, 1);
}

void	philo_sleep(t_philo *philo)
{
	int64_t	now;

	if (term(philo))
		return ;
	print_message(philo, "is sleeping");
	now = ft_gettimestamp(philo->data_ptr->start);
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
	now = ft_gettimestamp(philo->data_ptr->start);
	if (now - philo->last_food < philo->data_ptr->time_to_die)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (0);
	}
	philo->data_ptr->term += 1;
	print_message(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data_ptr->check_term);
	return (1);
}
