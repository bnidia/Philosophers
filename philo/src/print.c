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

//801 1 is died. Process is finished
//2806 4 has taken a fork
//All the philosophers ate 7 times. Process is finished

void	print(t_ph *p, t_time time, char *str)
{
	char	s[128];
	int		s_i;

	s_i = 0;
	itoa_append(s, &s_i, time.tv_sec);
	s[s_i++] = ' ';
	itoa_append(s, &s_i, time.tv_usec);
	s[s_i++] = ' ';
	str_append(s, &s_i, p->id);
	str_append(s, &s_i, str);
	pthread_mutex_lock(&p->m->mtx_print);
	write(1, s, s_i);
	pthread_mutex_unlock(&p->m->mtx_print);
}

void	print_all_ate(t_main *m)
{
	char	s[128];
	int 	s_i;

	s_i = 0;
	str_append(s, &s_i, "All the philosophers ate ");
	itoa_append(s, &s_i, m->number_of_eat);
	str_append(s, &s_i, " times. Process is finished\n");
	pthread_mutex_lock(&m->mtx_print);
	write(1, s, s_i);
	pthread_mutex_unlock(&m->mtx_print);
}
