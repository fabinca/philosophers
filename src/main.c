/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:29 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/28 15:55:23 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.nb_of_philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data.nb_meals = -10;
	else
		data.nb_meals = ft_atoi(argv[5]);
	data.dead = 0;
	pthread_mutex_init(&data.check_forks, NULL);
	data.fork_semaphores = (bool *)malloc(data.nb_of_philos * sizeof(bool));
	memset(data.fork_semaphores, 1, data.nb_of_philos * sizeof(bool));
	return (data);
}

t_philo	*init_philos(int philo_nb)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(philo_nb * sizeof(t_philo));
	i = 0;
	while (i < philo_nb)
	{
		philos[i].number = i;
		philos[i].nb_meals = 0;
		philos[i].last_food = get_timestamp();
		i++;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	int16_t		i;
	t_data		data;
	t_philo		*philos;
	pthread_t	*tid;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	data = init_data(argc, argv);
	philos = init_philos(data.nb_of_philos)
}

