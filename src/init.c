/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/10 20:31:29 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

static int	ft_init_philosophers(t_state *state)
{
	int			i;

	state->philo = (t_philo *)malloc(sizeof(t_philo)
									 * state->params->number_of_philosophers);
	state->mtx_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
									 * state->params->number_of_philosophers);
	if (state->philo == NULL || state->mtx_forks == NULL)
		return (ERR_CODE_MALLOC);
	i = 0;
	while (i < state->params->number_of_philosophers)
	{
		state->philo[i].id = i + 1;
		state->philo[i].count_of_eat = 0;
		state->philo[i].left_fork = &state->mtx_forks[i];
		if (i == state->params->number_of_philosophers - 1)
			state->philo[i].right_fork = &state->mtx_forks[0];
		else
			state->philo[i].right_fork = &state->mtx_forks[i + 1];

		// инициализация мютекса на поесть
		if (pthread_mutex_init(&state->philo[i].mtx_eat, NULL))
			return (ERR_CODE_MUTEX);
		state->philo[i].params = state->params;

		// инициализация мютекса на вилки
		if (pthread_mutex_init(&state->mtx_forks[i], NULL))
			return (ERR_CODE_MUTEX);
		i++;
	}
	return (0);
}