/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:53 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/26 10:15:05 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_philosophers(char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return ;
	pthread_mutex_init(&table->lock_write, NULL);
	pthread_mutex_init(&table->lock_death, NULL);
	pthread_mutex_init(&table->lock_eat, NULL);
	table->n_philos = ft_atol(av[1]);
	table->full_count = 0;
	table->is_end = false;
	table->start = get_time();
	table->forks = ft_init_forks(ft_atol(av[1]));
	table->philos = ft_init_philos(table, av);
	if (!table->forks || !table->philos)
		ft_destroy(table);
	ft_get2work(table);
	ft_destroy(table);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!ft_check_args(av))
			return (1);
		ft_philosophers(av);
	}
	else
		return (1);
	return (0);
}
