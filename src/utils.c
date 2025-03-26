/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:54:07 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/25 18:00:33 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	ft_atol(const char *str)
{
	unsigned long	result;
	int				i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

void	ft_destroy_forklst(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(table->forks[i]);
		i++;
	}
}

void	ft_free_prog(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	i = 0;
	while (i < table->n_philos)
	{
		free(table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table);
}

void	ft_destroy(t_table *table)
{
	if (table->forks)
		ft_destroy_forklst(table);
	pthread_mutex_destroy(&table->lock_write);
	pthread_mutex_destroy(&table->lock_death);
	pthread_mutex_destroy(&table->lock_eat);
	ft_free_prog(table);
}
