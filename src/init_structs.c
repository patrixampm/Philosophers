/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:01:53 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/25 17:55:03 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	**ft_init_forks(int n_philos)
{
	int				i;
	pthread_mutex_t	**fork_lst;

	fork_lst = malloc(n_philos * sizeof(pthread_mutex_t *));
	if (fork_lst == NULL)
		return (fork_lst = NULL);
	i = 0;
	while (i < n_philos)
	{
		fork_lst[i] = malloc(sizeof(pthread_mutex_t));
		if (fork_lst[i] == NULL)
			return (fork_lst = NULL);
		pthread_mutex_init(fork_lst[i], NULL);
		i++;
	}
	return (fork_lst);
}

static void	ft_s_f(t_philo *p, pthread_mutex_t **flst, int i, char **av)
{
	p->times_eaten = 0;
	p->n_philos = atol(av[1]);
	p->t_left = flst[i];
	if (i == 0)
	{
		if (ft_atol(av[1]) > 1)
			p->t_right = flst[ft_atol(av[1]) - 1];
		else
			p->t_right = NULL;
	}
	else
		p->t_right = flst[i - 1];
}

void	ft_init_p_mutex(t_table *table, t_philo *philo)
{
	philo->is_dead = &table->is_end;
	philo->last_meal = get_time();
	philo->meal_start = table->start;
	philo->lock_write = &table->lock_write;
	philo->lock_eat = &table->lock_eat;
	philo->lock_death = &table->lock_death;
}

t_philo	**ft_init_philos(t_table *table, char **av)
{
	size_t	i;
	t_philo	**philo_lst;

	philo_lst = malloc(ft_atol(av[1]) * sizeof(t_philo *));
	if (philo_lst == NULL)
		return (philo_lst = NULL);
	i = 0;
	while (i < ft_atol(av[1]))
	{
		philo_lst[i] = malloc(sizeof(t_philo));
		if (philo_lst[i] == NULL)
			return (philo_lst = NULL);
		ft_init_p_mutex(table, philo_lst[i]);
		philo_lst[i]->id = i + 1;
		philo_lst[i]->t2die = ft_atol(av[2]);
		philo_lst[i]->t2eat = ft_atol(av[3]);
		philo_lst[i]->t2sleep = ft_atol(av[4]);
		if (av[5])
			philo_lst[i]->n_t_eat = ft_atol(av[5]);
		else
			philo_lst[i]->n_t_eat = -1;
		ft_s_f(philo_lst[i], table->forks, i, av);
		i++;
	}
	return (philo_lst);
}
