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
	if (start_philo_lifes(m->philo, m->number_of_philosophers) != 0)
		return ((int)write(1, "start_philo_lifes() error\n" , 26));

	// Проверяем 1) количество приемов пищи и 2) смерть
	i = 0;
	while (42)
	{
		pthread_mutex_lock(&m->mtx_dead);
		if (m->dead == 1)
		{
			pthread_mutex_unlock(&m->mtx_dead);
			break ;
		}
		pthread_mutex_unlock(&m->mtx_dead);

		pthread_mutex_lock(&m->mtx_satisfied);
		if (m->satisfied == m->number_of_philosophers)
		{
			pthread_mutex_unlock(&m->mtx_satisfied);
			print_all_ate(m);
			break ;
		}
		pthread_mutex_unlock(&m->mtx_satisfied);

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
	// Сначала запускаем нечетных философов i = 0 у философа 1
	while (i < num_of_philo)
	{
		if (pthread_create(&p[i].tid, NULL, p_life, (void *) &p[i]) != 0)
			return ((int)write(1, "pthread_create() error!\n", 24));
		pthread_detach(p[i].tid);
		usleep(100); // какая задержка должна быть?
		i += 2;
	}
	i = 1;
	// Потом запускаем четных философов
	//usleep(1000000);
	while (i < num_of_philo)
	{
		if (pthread_create(&p[i].tid, NULL, p_life, (void *) &p[i]) != 0)
			return ((int)write(1, "pthread_create() error!\n", 24));
		pthread_detach(p[i].tid);
		usleep(100);
		i += 2;
	}
	return (0);
}
