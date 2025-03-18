
#include "philosophers.h"

void	ft_free_mutex(t_main *main, int i)
{
	if (main && i > 0)
		pthread_mutex_destroy(&main->print);
	if (main && i > 1)
		pthread_mutex_destroy(&main->stop);
	if (main && i > 2)
	{
		i = main->n_philos;
		while (--i >= 0)
			pthread_mutex_destroy(&main->philos[i].diner);
	}
	ft_free_philo(main);
}

void	ft_free_philo(t_main *main)
{
	if (main && main->philos)
		free(main->philos);
	if (main)
		ft_free_fork(main, main->n_philos);
}

void	ft_free_fork(t_main *main, int i)
{
	int	j;

	j = 0;
	if (main && main->forks)
	{
		while (j < i)
		{
			pthread_mutex_destroy(&main->forks[j]);
			j++;
		}
		free(main->forks);
	}
	ft_free_main(main);
}

void	ft_free_main(t_main *main)
{
	if (main)
		free(main);
}

void	ft_clear_end(t_main *main)
{
	int	i;

	if (main && main->philos)
	{
		i = -1;
		while (++i < main->n_philos)
		{
			pthread_mutex_destroy(&main->philos[i].diner);
			pthread_mutex_destroy(&main->philos[i].fini);
		}
		free(main->philos);
	}
	if (main && main->forks)
	{
		i = -1;
		while (++i < main->n_philos)
			pthread_mutex_destroy(&main->forks[i]);
		pthread_mutex_destroy(&main->print);
		pthread_mutex_destroy(&main->stop);
		free(main->forks);
	}
	if (main)
		free(main);
}
