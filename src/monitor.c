/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:37:13 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/26 10:17:28 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	ft_life(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_death);
	if (*philo->is_dead == true)
	{
		pthread_mutex_unlock(philo->lock_death);
		return (false);
	}
	pthread_mutex_unlock(philo->lock_death);
	return (true);
}

int	ft_get_full_count(t_table *table)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < table->n_philos)
	{
		if (table->philos[i]->times_eaten >= table->philos[i]->n_t_eat)
			count++;
		i++;
	}
	return (count);
}

bool	ft_death_time(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		pthread_mutex_lock(&t->lock_eat);
		if (get_time() - t->philos[i]->last_meal >= t->philos[i]->t2die)
		{
			print_action("died", t->philos[i], t->philos[i]->id, RED);
			pthread_mutex_lock(&t->lock_death);
			t->is_end = true;
			pthread_mutex_unlock(&t->lock_death);
			pthread_mutex_unlock(&t->lock_eat);
			return (false);
		}
		pthread_mutex_unlock(&t->lock_eat);
		i++;
	}
	return (true);
}

void	*ft_monitor(void *ph)
{
	t_table	*t;

	t = (t_table *)ph;
	while (1)
	{
		if (!ft_death_time(t))
			return (ph);
		if (t->philos[0]->n_t_eat != -1)
		{
			pthread_mutex_lock(&t->lock_eat);
			t->full_count = ft_get_full_count(t);
			if (t->full_count == t->n_philos
				|| t->philos[0]->n_t_eat == 0)
			{
				pthread_mutex_lock(&t->lock_death);
				t->is_end = true;
				pthread_mutex_unlock(&t->lock_death);
				pthread_mutex_unlock(&t->lock_eat);
				return (ph);
			}
			pthread_mutex_unlock(&t->lock_eat);
		}
	}
}
