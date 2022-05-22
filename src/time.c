/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/03 16:53:36 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* get_time() сохраняет в статической переменной время начала работы программы.
 * Возвращает время, которое прошло с начала работы программы */
long	get_time(void)
{
	static struct timeval	t;
	static long				start_time;
	static long				work_time;

	gettimeofday(&t, NULL);
	if (start_time == 0)
		start_time = t.tv_sec * 1000 + t.tv_usec / 1000;
	work_time = t.tv_sec * 1000 + t.tv_usec / 1000 - start_time;
	return (work_time);
}

void	ft_usleep(long time)
{
	long	t;

	t = get_time();
	while (1)
	{
		if (get_time() - t >= time)
			break ;
		usleep(1);
	}
}
