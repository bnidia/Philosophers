/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/03 16:15:04 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	yellow(void);
static void	reset(void);

/** @name print
 * @description prints to the screen logs about philosopher actions
 * @param t_time time - time to print in message, t_ph *p - used to find a
 * number id of philosopher, char *str - string to print
 * @return nothing
 * @author bnidia													*/
void	print(t_time time, t_ph *p, char *str, bool lock)
{
	static t_mutex	screen = PTHREAD_MUTEX_INITIALIZER;
	int				id;

	id = p->id;
	pthread_mutex_lock(&screen);
	if (lock == true && str == NULL)
		return ;
	if (id % 2 == 0)
		yellow();
	printf("%ld%03ld %d %s", \
			time.tv_sec, \
			(time.tv_usec + 500) / 1000, \
			id, \
			str \
	);
	if (id % 2 == 0)
		reset();
	if (lock == false)
		pthread_mutex_unlock(&screen);
}

/** @name yellow
 * @description sets printing font to yellow colour
 * @param nothing
 * @return nothing
 * @author bnidia													*/
static void	yellow(void)
{
	printf("\e[33m");
}

/** @name reset
 * @description resets colour for printing font
 * @param nothing
 * @return nothing
 * @author bnidia													*/
static void	reset(void)
{
	printf("\e[0m");
}
