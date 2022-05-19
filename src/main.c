/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:29 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/19 12:32:34 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	init_data(int argc, char **argv)
{
	t_data	d;

	d.nb_p = ft_atoi(argv[1]);
	d.time_to_die = ft_atoi(argv[2]);
	d.time_to_eat = ft_atoi(argv[3]);
	d.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		d.nb_meals = -10;
	else
		d.nb_meals = ft_atoi(argv[5]);
	d.term = 0;
	d.philos_finished_nbm = 0;
	d.fork_state = (bool *)malloc(d.nb_p * sizeof(bool));
	memset(d.fork_state, 1, d.nb_p * sizeof(bool));
	pthread_mutex_init(&d.check_term, NULL);
	pthread_mutex_init(&d.enough_meals, NULL);
	d.f_mutex = (pthread_mutex_t *)malloc(d.nb_p * sizeof(pthread_mutex_t));
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
		pthread_mutex_init(&(data->f_mutex[i]), NULL);
		philos[i].number = i;
		if (i > 0)
			philos[i].left = i - 1;
		else
			philos[i].left = data->nb_p - 1;
		philos[i].nb_meals = 0;
		philos[i].data_ptr = data;
		philos[i].hand_fork[0] = 0;
		philos[i].hand_fork[1] = 0;
		i++;
	}
	return (philos);
}

int	invalid_input(int argc, char **argv)
{
	int	arg;

	if (argc < 5 || argc > 6)
	{
		printf("%sUsage: ./philo number_of_philosophers time_to_die ", RED);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]%s\n", DEF);
		return (1);
	}
	arg = 1;
	while (arg++ < argc - 1)
	{
		if (!ft_str_is_numeric(argv[arg]))
		{
			printf("%s%s: Natural numbers required.%s\n", RED, argv[arg], DEF);
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
