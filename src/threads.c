/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:07:46 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/26 10:17:33 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_action(char *str, t_philo *p, int id, char *color)
{
	long	time;

	if (ft_life(p))
	{
		pthread_mutex_lock(p->lock_write);
		time = get_time() - p->meal_start;
		printf("%s[%ld] %d %s\n", color, time, id, str);
		pthread_mutex_unlock(p->lock_write);
	}
}

size_t	get_time(void)
{
	struct timeval	time;
	size_t			result;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (result = time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milisec)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milisec)
		usleep(1);
	return (0);
}

void	ft_get2work(t_table *table)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &ft_monitor, table) != 0)
		ft_destroy(table);
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&ft_routine, table->philos[i]) != 0)
			ft_destroy(table);
		i++;
	}
	pthread_join(monitor, NULL);
	i--;
	while (i >= 0)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i--;
	}
}
