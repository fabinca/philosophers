/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:29 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/29 15:03:57 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	init_data(int argc, char **argv)
{
	t_data	d;
	int		i;

	d.nb_p = ft_atoi(argv[1]);
	d.time_to_die = ft_atoi(argv[2]);
	d.time_to_eat = ft_atoi(argv[3]);
	d.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		d.nb_meals = -10;
	else
		d.nb_meals = ft_atoi(argv[5]);
	d.dead = 0;
	d.philos_finished_nbm = 0;
	pthread_mutex_init(&d.incr_philos_finished, NULL);
	pthread_mutex_init(&d.check_dead, NULL);
	pthread_mutex_init(&d.check_mutex, NULL);
	d.fork_semaphores = (bool *)malloc(d.nb_p * sizeof(bool));
	memset(d.fork_semaphores, 1, d.nb_p * sizeof(bool));
	d.f_mutex = (pthread_mutex_t *)malloc(d.nb_p * sizeof(pthread_mutex_t));
	i = 0;
	while (i++ < d.nb_p)
		pthread_mutex_init(&d.f_mutex[i], NULL);
	return (d);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(data->nb_p * sizeof(t_philo));
	i = 0;
	while (i < data->nb_p)
	{
		philos[i].number = i;
		if (i > 0)
			philos[i].left = i - 1;
		else
			philos[i].left = data->nb_p - 1;
		philos[i].nb_meals = 0;
		philos[i].data_ptr = data;
		i++;
	}
	return (philos);
}

int	invalid_input(int argc, char **argv)
{
	int	arg;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	arg = 1;
	while (arg++ < argc - 1)
	{
		if (!ft_str_is_numeric(argv[arg]))
		{
			printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\
			\n%s is not numeric.\n", argv[arg]);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int16_t		i;
	t_data		data;
	t_philo		*philos;
	pthread_t	*tid;

	if (invalid_input(argc, argv))
		return (0);
	data = init_data(argc, argv);
	tid = (pthread_t *)malloc(sizeof(pthread_t) * data.nb_p);
	philos = init_philos(&data);
	i = 0;
	while (i < data.nb_p)
	{
		pthread_create(&tid[i], NULL, &philo_thread, &philos[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_p)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	free_all(tid, data, philos);
	return (0);
}
