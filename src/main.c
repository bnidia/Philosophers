/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/02 14:33:00 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int			err;
	t_main		m;

	if (init(&m, argc, argv) != 0)
		return (m.err);
	if (simulation(&m) !=0)
		return (m.err);
	memory_clearing(&m);
	return (m.err);
}
