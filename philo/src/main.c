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

/** @name main
 * @description starting point of the program
 * @param int argc, char *argv[] - command line parameters
 * @return 0 on success, other values on error
 * @author bnidia (doxygen)								*/
int	main(int argc, char *argv[])
{
	t_main		m;

	m = (t_main){};
	if (init(&m, argc, argv) != 0)
		return (printf("init() error\n"));
	if (simulation(&m) != 0)
		return (printf("simulation() error\n"));
	memory_clearing(&m);
	return (0);
}
