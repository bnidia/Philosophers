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

/** @name dead_handler
 * @description controls number of eat, when it equals to desired number of eat
 * @param bool set_dead true if dead, false if need to check others dead
 * @return true someone is dead, false - no one is dead
 * @author bnidia													*/
bool	dead_handler(t_ph *p, bool set_dead)
{
	static t_mutex	mtx_dead = PTHREAD_MUTEX_INITIALIZER;
	static bool		dead = false;

	if (p && timercmp(&p->event, &p->eat_before, >))
		set_dead = true;
	pthread_mutex_lock(&mtx_dead);
	if (set_dead)
		dead = true;
	if (dead)
	{
		pthread_mutex_unlock(&mtx_dead);
		return (true);
	}
	pthread_mutex_unlock(&mtx_dead);
	return (false);
}
