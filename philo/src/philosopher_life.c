/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/24 15:13:42 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_life(void *args)
{
	t_ph		*p;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;

	p = (t_ph *)args;
	time_to_die = p->m->time_to_die;
	time_to_eat = p->m->time_to_eat;
	time_to_sleep = p->m->time_to_sleep;
	gettimeofday(&p->t_last_time_eat, NULL);
	while (42)
	{

// первая вилка
		pthread_mutex_lock(p->left_fork);
		gettimeofday(&p->t_event, NULL);
		//printf("взял вилку philo %s s%ld u%ld\n", p->id, p->t_event.tv_sec, p->t_event.tv_usec);
		print(p, p->t_event, YELLOW " has taken a fork\n" YELLOW_RESET);
// вторая вилка
		pthread_mutex_lock(p->right_fork);
// начал есть
		gettimeofday(&p->t_event, NULL);
// смерть? проверка
		pthread_mutex_lock(&p->m->mtx_dead);
		if (p->m->dead == 1)
		{
			pthread_mutex_unlock(p->left_fork);
			pthread_mutex_unlock(p->right_fork);
			pthread_mutex_unlock(&p->m->mtx_dead);
			break;
		}
		pthread_mutex_unlock(&p->m->mtx_dead);

// смерть? не успел поесть
		convert_time(&p->t_last_time_eat, time_to_die);
		if (timercmp(&p->t_event, &p->t_last_time_eat, >))
		{
			pthread_mutex_lock(&p->m->mtx_dead);
			p->m->dead = 1;
			print(p, p->t_event, " is died. Process is finished\n");
			print(p, p->t_last_time_eat, " debug. p->t_last_time_eat\n");
			pthread_mutex_unlock(&p->m->mtx_dead);
			pthread_mutex_unlock(p->left_fork);
			pthread_mutex_unlock(p->right_fork);
			break;
		}
// продолжаем есть
		print(p, p->t_event, " has taken a fork\n");
		print(p, p->t_event, " is eating\n");

// поел, отмечаем когда поел
		convert_time(&p->t_event, time_to_eat);
		p->t_last_time_eat = p->t_event;

		sleep_to(p->t_event);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
// sleeping

		gettimeofday(&p->t_event, NULL);
		//printf("положил вилки philo %s s%ld u%ld\n", p->id, p->t_event.tv_sec, p->t_event.tv_usec);

		p->count_of_eat--;
		if (p->count_of_eat == 0)
		{
			pthread_mutex_lock(&p->m->mtx_satisfied);
			p->m->satisfied++;
			pthread_mutex_unlock(&p->m->mtx_satisfied);
			break;
		}

		print(p, p->t_event, " is sleeping\n");
		convert_time(&p->t_event, time_to_sleep);
		sleep_to(p->t_event);

// thinking
		print(p, p->t_event, " is thinking\n");
	}
	return ((void *)0);
}

