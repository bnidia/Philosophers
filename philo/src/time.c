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
#include <unistd.h>
/* You can use macros available in standard libraries, only if those
 * ones are allowed in the scope of the given project.
 * timercmp(&t, &t, <) - time comparison macro */

/** @name sleep_to
 * @description sleeps from t_event time milliseconds
 * @param t_time t_event, int time
 * @return void
 * @author bnidia										*/
void	sleep_to(t_time t_event, int time)
{
	t_time	t_current;
	long	sleep_time;

	calc_time_sum(&t_event, time);
	sleep_time = time * 1000;
	while (!gettimeofday(&t_current, NULL) && timercmp(&t_current, &t_event, <))
	{
		usleep(sleep_time * 9 / 10);
		sleep_time -= sleep_time * 9 / 10;
	}
}

/** @name calc_time_sum
 * @description adds time in milliseconds to the t_event
 * @param t_time *t_event - where to add, long time - what to add
 * @return void, processed value saves in t_time *t_event
 * @author bnidia										*/
t_time	calc_time_sum(t_time *t_event, long time)
{
	t_event->tv_sec += time / 1000;
	t_event->tv_usec += time % 1000 * 1000;
	if (t_event->tv_usec >= 1000000)
	{
		t_event->tv_sec++;
		t_event->tv_usec -= 1000000;
	}
	return (*t_event);
}
