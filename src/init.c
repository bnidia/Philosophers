/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/10 20:31:29 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philosophers(t_main *m);

int	init(t_main *m, int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
	// Надо проверить подачу 001 философа
		m->number_of_philosophers = ft_atoi_zero(argv[1]);
		m->time_to_die = ft_atoi_zero(argv[2]);
		m->time_to_eat = ft_atoi_zero(argv[3]);
		m->time_to_sleep = ft_atoi_zero(argv[4]);
		if ((*argv[1] != '0' && m->number_of_philosophers == 0)
			|| (*argv[2] != '0' && m->time_to_die == 0)
			|| (*argv[3] != '0' && m->time_to_eat == 0)
			|| (*argv[3] != '0' && m->time_to_sleep == 0))
			return (1);
	}
	if (argc == 6)
	{
		m->number_of_philosophers = ft_atoi_zero(argv[5]);
		if (*argv[5] != '0' && m->number_of_philosophers == 0)
			return (1);
	}
	// Используем ft_atoi_zero которая возвращает 0 как ошибку
	// Поэтому нужно проверять на истинный ноль
	// Переменные уже инициализированы 0
	if (argc < 5 || argc > 6)
		return (1);
	init_philosophers(m);
	return (0);
}

static int	init_philosophers(t_main *m)
{
	int			i;

	i = m->number_of_philosophers;
	m->philo = (t_ph *)malloc(sizeof(t_ph) * i);
	m->mtx_forks = (mutex *)malloc(sizeof(mutex) * i);
	if (m->philo == NULL || m->mtx_forks == NULL)
	{
		m->err = 2;
		return (2);
	}
	i = 0;
	while (i < m->number_of_philosophers)
	{
		m->philo[i] = (t_ph){};
		m->philo[i].id = i;

		// раздаем мьютексы на вилки
		m->err = pthread_mutex_init(&m->mtx_forks[i], NULL);
		if (m->err)
			return (3);
		m->philo[i].left_fork = &m->mtx_forks[i];
		// Последнему философу выдаем в правую руку вилку с меньшим числом
		// как нам завещал в 1965 году Эдсгер Дейкстра
		if (i == m->number_of_philosophers - 1)
			m->philo[i].right_fork = &m->mtx_forks[0];
		else
			m->philo[i].right_fork = &m->mtx_forks[i + 1];

		// инициализация мютекса на поесть
		m->err = pthread_mutex_init(&m->philo[i].mtx_eat, NULL);
		if (m->err)
			return (4);
		m->philo[i].params = m;
		i++;
	}
	return (0);
}
