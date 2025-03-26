/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/26 10:17:20 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>

# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define RED "\033[0;31m"
# define WHITE "\033[37;1m"

//	STRUCTURES
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			last_meal;
	size_t			meal_start;
	size_t			t2die;
	size_t			t2eat;
	size_t			t2sleep;
	int				n_t_eat;
	int				times_eaten;
	int				n_philos;
	pthread_mutex_t	*lock_write;
	pthread_mutex_t	*lock_death;
	pthread_mutex_t	*lock_eat;
	pthread_mutex_t	*t_left;
	pthread_mutex_t	*t_right;
	bool			*is_dead;
}	t_philo;

typedef struct s_table
{
	size_t			start;
	t_philo			**philos;
	int				n_philos;
	int				full_count;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	**forks;
	bool			is_end;
}	t_table;

//	FUNCTIONS
// utils
unsigned long	ft_atol(const char *str);
void			ft_free_prog(t_table *table);
void			ft_destroy_forklst(t_table *table);
void			ft_destroy(t_table *table);

// argument checks
bool			ft_check_args(char **av);

// initiate structs
void			ft_init_p_mutex(t_table *table, t_philo *philo);
pthread_mutex_t	**ft_init_forks(int n_philos);
t_philo			**ft_init_philos(t_table *table, char **av);

// philosophers
void			print_action(char *str, t_philo *p, int id, char *color);
size_t			get_time(void);
int				ft_usleep(size_t milisec);
int				ft_get_full_count(t_table *table);
void			*ft_monitor(void *ph);
void			ft_grab_forks(t_philo *p);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			ft_think(t_philo *philo);
void			*ft_routine(void *ph);
bool			ft_life(t_philo *philo);
void			ft_get2work(t_table *table);
void			ft_philosophers(char **av);

#endif
