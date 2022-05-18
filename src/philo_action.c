/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 18:11:22 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	print_message(int num, char *message)
{
	printf("%li philosopher %i %s.\n", ft_gettimestamp(), num + 1, message);
}

void	take_left_fork(t_philo *philo)
{
	if (philo->hand_fork[0] == 1 || term(philo))
		return ;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->left]);
	if (philo->data_ptr->fork_state[philo->left] == 1)
	{
		philo->data_ptr->fork_state[philo->left] = 0;
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
		philo->hand_fork[0] = 1;
		if (term(philo))
			return ;
		print_message(philo->number, "has taken left fork");
		//printf("%li philosopher %i has taken left fork.\n", ft_gettimestamp(), philo->number + 1);
	}
	else
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
}

void	take_right_fork(t_philo *philo)
{
	if (philo->hand_fork[1] == 1 || term(philo))
		return ;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->number]);
	if (philo->data_ptr->fork_state[philo->number] == 1)
	{
		philo->data_ptr->fork_state[philo->number] = 0;
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
		philo->hand_fork[1] = 1;
		if (term(philo))
			return ;
		print_message(philo->number, "has taken right fork");
		//printf("%li philosopher %i has taken right fork.\n", ft_gettimestamp(), philo->number + 1);
	}
	else
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
}

void	think(t_philo *philo, int64_t time)
{
	if (philo->data_ptr->term > 0)
		return ;
	print_message(philo->number, "is thinking");
	//printf("%li philosopher %i is thinking.\n", ft_gettimestamp(), philo->number + 1);
	usleep(time);
}

void	put_down_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->number]);
	philo->data_ptr->fork_state[philo->number] = 1;
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
	philo->hand_fork[1] = 0;
}

void	put_down_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->left]);
	philo->data_ptr->fork_state[philo->left] = 1;
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
	philo->hand_fork[0] = 0;
}

void	eat(t_philo *philo)
{
	int64_t	now;

	if (philo->data_ptr->term > 0)
		return ;
	print_message(philo->number, "is eating");
	//printf("%li philosopher %i is eating. (%i)\n", ft_gettimestamp(), philo->number + 1, philo->nb_meals);
	philo->nb_meals += 1;
	now = ft_gettimestamp();
	if (philo->nb_meals == philo->data_ptr->nb_meals)
	{
		//pthread_mutex_lock(&philo->data_ptr->incr_philos_finished);
		philo->data_ptr->philos_finished_nbm += 1;
		//pthread_mutex_unlock(&philo->data_ptr->incr_philos_finished);
		if (philo->data_ptr->philos_finished_nbm == philo->data_ptr->nb_p)
		{
			//pthread_mutex_lock(&philo->data_ptr->check_term);
			philo->data_ptr->term += 1;
			//pthread_mutex_unlock(&philo->data_ptr->check_term);
		}
	}
	usleep(philo->data_ptr->time_to_sleep * 1000 -(ft_gettimestamp() - now));
	philo->last_food = now;
	put_down_left_fork(philo);
	put_down_right_fork(philo);
}

void	philo_sleep(t_philo *philo)
{
	int64_t	now;

	if (philo->data_ptr->term > 0)
		return ;
	print_message(philo->number, "is sleeping");
	//printf("%li philosopher %i is sleeping.\n", ft_gettimestamp(), philo->number + 1);
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

	//pthread_mutex_lock(&philo->data_ptr->check_term);
	if (philo->data_ptr->term > 0)
	{
		//pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (1);
	}
	now = ft_gettimestamp();
	if (now - philo->last_food < philo->data_ptr->time_to_die)
	{
		//pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (0);
	}
	//pthread_mutex_unlock(&philo->data_ptr->check_term);
	print_message(philo->number, "died");
	//printf("%li philosopher %i died.\n", ft_gettimestamp(), philo->number + 1);
	philo->data_ptr->term += 1;
	return (1);
}
