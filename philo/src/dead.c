/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/07/02 10:42:11 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*consumer(void *args);

/** @name dead_handler
 * @description controls number of eat, when it equals to desired number of eat
 * @param bool set_dead true if dead, false if need to check others dead
 * @return true someone is dead, false - no one is dead
 * @author bnidia													*/
bool	dead_handler(t_ph *p)
{
	pthread_t		tid;

	if (pthread_create(&tid, NULL, consumer, (void *) p) != 0)
		return (printf("pthread_create() error!\n"));
	pthread_detach(tid);
	return (0);
}

void	*consumer(void *args)
{
	t_ph		*p;
	t_time		best_before;
	t_time		event;
	long long	diff;

	p = (t_ph *)args;
	diff = 1;
	while (diff >= 0 && usleep(100) == 0)
	{
		if (diff > 100)
		{
			usleep(diff * 99 / 100);
			diff -= diff * 99 / 100;
		}
		else
		{
			gettimeofday(&event, NULL);
			best_before = read_write_best_before(p, READ, NULL);
			diff = calc_time_diff(&best_before, &event);
		}
	}
	print(event, p, "died\n", true);
	read_write_dead_flag(WRITE, true);
	return (false);
}

t_time	read_write_best_before(t_ph *p, int flag, t_time *set_value)
{
	static t_mutex	mtx_best_before = PTHREAD_MUTEX_INITIALIZER;
	t_time			best_before;

	if (flag == READ)
	{
		pthread_mutex_lock(&mtx_best_before);
		best_before = p->best_before;
		pthread_mutex_unlock(&mtx_best_before);
	}
	if (flag == WRITE)
	{
		pthread_mutex_lock(&mtx_best_before);
		p->best_before = *set_value;
		best_before = *set_value;
		pthread_mutex_unlock(&mtx_best_before);
	}
	return (best_before);
}

bool	read_write_dead_flag(int flag, bool set_dead)
{
	static t_mutex	mtx_dead = PTHREAD_MUTEX_INITIALIZER;
	static bool		dead = false;
	bool			return_value;

	if (flag == READ)
	{
		pthread_mutex_lock(&mtx_dead);
		return_value = dead;
		pthread_mutex_unlock(&mtx_dead);
	}
	if (flag == WRITE)
	{
		pthread_mutex_lock(&mtx_dead);
		dead = set_dead;
		pthread_mutex_unlock(&mtx_dead);
		return (true);
	}
	return (return_value);
}
