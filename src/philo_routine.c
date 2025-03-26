/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:34:18 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/25 17:59:41 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_grab_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->t_right);
		print_action("has taken a fork", p, p->id, YELLOW);
		pthread_mutex_lock(p->t_left);
		print_action("has taken a fork", p, p->id, ORANGE);
	}
	else
	{
		pthread_mutex_lock(p->t_left);
		print_action("has taken a fork", p, p->id, ORANGE);
		pthread_mutex_lock(p->t_right);
		print_action("has taken a fork", p, p->id, YELLOW);
	}
}

void	ft_eat(t_philo *philo)
{
	ft_grab_forks(philo);
	print_action("is eating", philo, philo->id, GREEN);
	pthread_mutex_lock(philo->lock_eat);
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->lock_eat);
	ft_usleep(philo->t2eat);
	pthread_mutex_unlock(philo->t_right);
	pthread_mutex_unlock(philo->t_left);
}

void	ft_sleep(t_philo *philo)
{
	print_action("is sleeping", philo, philo->id, BLUE);
	ft_usleep(philo->t2sleep);
}

void	ft_think(t_philo *philo)
{
	print_action("is thinking", philo, philo->id, WHITE);
	ft_usleep(2);
}

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	if (philo->n_philos == 1)
	{
		print_action("has taken a fork", philo, philo->id, BLUE);
		ft_usleep(philo->t2die);
		return (ph);
	}
	while (ft_life(philo))
	{
		if (ft_life(philo))
			ft_eat(philo);
		if (ft_life(philo))
			ft_sleep(philo);
		if (ft_life(philo))
			ft_think(philo);
	}
	return (ph);
}
