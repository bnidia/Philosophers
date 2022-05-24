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

static void	ft_eat(t_ph *p);

void	*process_eat_sleep_think(void *args)
{
	t_ph		*p;

	p = (t_ph *)args;
	while (1)
	{
		ft_eat(p);
		if (p->count_of_eat != -1
			&& (p->count_of_eat >= p->count_of_eat))
			break ;
		print(p, " is sleeping");
		ft_usleep(p->params->time_to_sleep);
		print(p, " is thinking");
	}
	return ((void *)0);
}

static void	ft_eat(t_ph *p)
{
	pthread_mutex_lock(p->left_fork);
	print(p, " has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print(p, " has taken a fork");

	print(p, " is eating");
	ft_usleep(p->params->time_to_eat);
	p->last_time_eat = get_time();
	if (p->count_of_eat != -1)
		p->count_of_eat++;
	pthread_mutex_unlock(p->right_fork); //поменять местами
	pthread_mutex_unlock(p->left_fork);
}