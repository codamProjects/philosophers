
#include "philosophers.h"

static void	*ft_philo_mutex(t_main *main, int i)
{
	while (main && ++i < main->n_philos)
	{
		if (pthread_mutex_init(&main->philos[i].diner, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&main->philos[i].diner);
			ft_free_mutex(main, 2);
			return (ft_print_error(INIT), NULL);
		}
	}
	i = -1;
	while (main && ++i < main->n_philos)
	{
		if (pthread_mutex_init(&main->philos[i].fini, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&main->philos[i].fini);
			ft_free_mutex(main, 3);
			return (ft_print_error(INIT), NULL);
		}
	}
	return (main);
}

static void	*ft_init_mutex(t_main *main)
{
	if (main && pthread_mutex_init(&main->print, NULL) != 0)
	{
		ft_free_philo(main);
		return (ft_print_error(INIT), NULL);
	}
	if (main && pthread_mutex_init(&main->stop, NULL) != 0)
	{
		ft_free_mutex(main, 1);
		return (ft_print_error(INIT), NULL);
	}
	return (ft_philo_mutex(main, -1));
}

static void	*ft_init_philos(t_main *main)
{
	int		i;

	if (!main)
		return (NULL);
	main->philos = (t_philo *)malloc(sizeof(t_philo) * main->n_philos);
	if (!main->philos)
	{
		ft_free_fork(main, main->n_philos);
		return (ft_print_error(MALLOC), NULL);
	}
	i = -1;
	while (++i < main->n_philos)
	{
		main->philos[i].num = i + 1;
		main->philos[i].fork_s = i;
		main->philos[i].fork_n = (i + 1) % main->n_philos;
		main->philos[i].main = main;
		main->philos[i].d_time = main->t_die;
		main->philos[i].done = 0;
	}
	return (main);
}

static void	*ft_init_forks(t_main *main)
{
	int	i;

	if (!main)
		return (NULL);
	i = main->n_philos;
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i);
	if (!main->forks)
	{
		ft_free_main(main);
		return (ft_print_error(MALLOC), NULL);
	}
	i = 0;
	while (i < main->n_philos)
	{
		if (pthread_mutex_init(&main->forks[i], NULL) != 0)
		{
			ft_free_fork(main, i);
			ft_print_error(INIT);
			return (NULL);
		}
		i++;
	}
	return (main);
}

void	*ft_fill_main(int argc, char **argv, t_main *main)
{
	if (!main)
		return (NULL);
	main->n_philos = (int)ft_atoi(argv[1]);
	main->t_die = (u_int64_t)ft_atoi(argv[2]);
	main->t_eat = (u_int64_t)ft_atoi(argv[3]);
	main->t_sleep = (u_int64_t)ft_atoi(argv[4]);
	if (argc == 6)
		main->rounds = (int)ft_atoi(argv[5]);
	else
		main->rounds = -1;
	main->all_done = 0;
	main->died = 0;
	if (main->rounds == 0 || main->n_philos <= 0 || main->n_philos > MAX_PHILOS \
		|| main->t_die < 60 || main->t_eat < 60 || main->t_sleep < 60)
		return (ft_print_error(LOWVAL), ft_free_main(main), NULL);
	if (!ft_init_forks(main))
		return (NULL);
	if (!ft_init_philos(main))
		return (NULL);
	if (!ft_init_mutex(main))
		return (NULL);
	return (main);
}
