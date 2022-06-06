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
	if (argc != 5 && argc != 6)
		return ((int)write(1, "Arguments error. Need 4 or 5.\n", 30));
	if (ft_atoi_r(argv[1], &m->number_of_philosophers)
		|| ft_atoi_r(argv[2], &m->time_to_die)
		|| ft_atoi_r(argv[3], &m->time_to_eat)
		|| ft_atoi_r(argv[4], &m->time_to_sleep))
		return (1);
	if (argc == 6 && ft_atoi_r(argv[5], &m->number_of_eat))
		return (1);
	// Используем ft_atoi_r которая возвращает 1 как ошибку
	// Переменные уже инициализированы 0
	if (m->number_of_philosophers < 1 || m->time_to_die < 0
		|| m->time_to_eat < 0 || m->time_to_sleep < 0
		|| (argc == 6 && m->number_of_eat < 0))
		return ((int)write(1, "Invalid arguments.\n", 19));
	if (init_philosophers(m) != 0)
		return ((int)write(1, "init_philosophers error\n", 24));
	if (pthread_mutex_init(&m->mtx_print, NULL) != 0)
		write(1, "Mutex print. Init error.\n", 25);
	return (0);
}

static int	init_philosophers(t_main *m)
{
	int	i;
	int s_i;

	i = m->number_of_philosophers;
	m->philo = (t_ph *)malloc(sizeof(t_ph) * i);
	m->mtx_forks = (mutex *)malloc(sizeof(mutex) * i);
	if (m->philo == NULL || m->mtx_forks == NULL)
		return ((int)write(1, "Memory. Malloc error.\n", 22));
	// нумерация философов в выводе начинается с одного
	i = 0;

	while (i < m->number_of_philosophers)
	{
		m->philo[i] = (t_ph){};
		s_i = 0;
		itoa_append(m->philo[i].id, &s_i, i + 1);
		m->philo[i].count_of_eat = m->number_of_eat;

		// раздаем мьютексы на вилки
		if (pthread_mutex_init(&m->mtx_forks[i], NULL) != 0)
			return ((int)write(1, "Mutex fork. Init error.\n", 24));
		m->philo[i].left_fork = &m->mtx_forks[i];
		// Последнему философу выдаем в правую руку вилку с меньшим числом
		// как нам завещал в 1965 году Эдсгер Дейкстра
		if (i == m->number_of_philosophers - 1)
			m->philo[i].right_fork = &m->mtx_forks[0];
		else
			m->philo[i].right_fork = &m->mtx_forks[i + 1];

		m->philo[i].m = m;
		i++;
	}
	return (0);
}
