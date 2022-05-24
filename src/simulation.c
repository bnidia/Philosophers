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

static int start_philo_lifes(t_ph *p, int num_of_philo);

int	simulation(t_main *m)
{
	int i;

	// Даем жизнь философам
	m->err = start_philo_lifes(m->philo, m->number_of_philosophers);
	if (m->err != 0)
		return (m->err);

	// Проверяем 1) количество приемов пищи и 2) смерть
	// Количество приемов должно быть ноль у всех
	// это будет означать что можно заканчивать
	// Смерть. Если этот цикл быстрый, можно проверять
	// время между приемами пищи тут
	// Но лучше это делать в самом философе
	i = 0;
	// тут доделать
	while (m->philo[i].count_of_eat != 0)
	{
		i++;
		if (i == m->number_of_philosophers)
			i = 0;
	}
	return (0);
}

static int start_philo_lifes(t_ph *p, int num_of_philo)
{
	int		i;

	i = 0;
	// Сначала запускаем четных философов
	while (i < num_of_philo)
	{
		if (pthread_create(&p->tid, NULL, p_life, (void *) p) != 0)
			return (6);
		p[i].last_time_eat = get_time();
		pthread_detach(p->tid);
		usleep(100); // какая задержка должна быть?
		i += 2;
	}
	i = 1;
	// Потом запускаем нечетных философов
	while (i < num_of_philo)
	{
		if (pthread_create(&p->tid, NULL, p_life, (void *) p) != 0)
			return (6);
		p[i].last_time_eat = get_time();
		pthread_detach(p->tid);
		usleep(100);
		i += 2;
	}
	return (0);
}
