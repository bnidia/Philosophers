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
/* You can use macros available in standard libraries, only if those
 * ones are allowed in the scope of the given project. */

/* get_time() сохраняет в статической переменной время начала работы программы.
 * Возвращает время, которое прошло с начала работы программы
 * timercmp(&t, &t, <) - макрос сравнения времени */

void sleep_to(t_time t_event)
{
	t_time	t_current;

	while (!gettimeofday(&t_current, NULL) && timercmp(&t_current, &t_event, <))
		usleep(1);
}

void convert_time(t_time *t_event, long time)
{
	t_event->tv_sec += time / 1000;
	t_event->tv_usec += time % 1000 * 1000;
	if (t_event->tv_usec >= 1000000)
	{
		t_event->tv_sec++;
		t_event->tv_usec -= 1000000;
	}
}