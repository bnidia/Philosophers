/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/08 13:33:45 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int start_philosophers_lifes(t_main *m);

int	simulation(t_main *m)
{
	int i;

	// Даем жизнь философам
	m->err = start_philosophers_lifes(m);
	if (m->err != 0)
		return (m->err);

	// Проверяем 1) количество приемов пищи и 2) смерть
	// Количество приемов должно быть ноль у всех
	// это будет означать что можно заканчивать
	// Смерть. Если этот цикл быстрый, можно проверять
	// время между приемами пищи тут
	// Но лучше это делать в самом философе
	i = 0;
	while (m->philo[i].count_of_eat != 0)
	{
		i++;
		if (i == m->number_of_philosophers)
			i = 0;
	}
	return (0);
}

static int start_philosophers_lifes(t_main *m)
{
	int		i;
	t_ph	*p;

	i = 0;
	while (i < m->number_of_philosophers)
	{
		p = &m->philo[i];
		p->last_time_eat = get_time();
		if (pthread_create(&p->tid, NULL, p_life, (void *) p) != 0)
			return (6);
		pthread_detach(p->tid);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < m->number_of_philosophers)
	{
		p = &m->philo[i];
		p->last_time_eat = get_time();
		if (pthread_create(&p->tid, NULL, p_life, (void *) p) != 0)
			return (6);
		pthread_detach(p->tid);
		usleep(100);
		i += 2;
	}
	return (0);
}
