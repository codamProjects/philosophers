
#include "philosophers.h"

static int	ft_check_all_done(t_philo *p)
{
	if (!p)
		return (1);
	pthread_mutex_lock(&p->fini);
	if (p->done >= p->main->rounds)
	{
		pthread_mutex_unlock(&p->fini);
		pthread_mutex_lock(&p->main->stop);
		if (p->main->all_done == p->main->n_philos)
			return (pthread_mutex_unlock(&p->main->stop), 1);
		pthread_mutex_unlock(&p->main->stop);
	}
	else
		pthread_mutex_unlock(&p->fini);
	return (0);
}

static void	*ft_died(void *m_void)
{
	t_main	*m;
	int		i;

	m = (t_main *)m_void;
	i = 0;
	while (m && i < m->n_philos && &m->philos[i])
	{
		if (m->rounds != -1 && ft_check_all_done(&m->philos[i]))
			return ((void *)0);
		pthread_mutex_lock(&m->philos[i].diner);
		if (m->philos[i].d_time <= (ft_time() - m->start_t))
		{
			pthread_mutex_unlock(&m->philos[i].diner);
			ft_print_message(&m->philos[i], DIED);
			return ((void *)1);
		}
		pthread_mutex_unlock(&m->philos[i].diner);
		i = (i + 1) % m->n_philos;
	}
	return ((void *)0);
}

static int	ft_threads(t_main *m)
{
	int			i;
	int			j;

	if (!m)
		return (1);
	i = -1;
	m->start_t = ft_time();
	if (pthread_create(&m->death, NULL, ft_died, (void *)m) != 0)
		return (ft_print_error(CREATE), 1);
	while (++i < m->n_philos)
	{
		if (pthread_create(&m->philos[i].tid, NULL, ft_p_thread, \
			(void *)&m->philos[i]) != 0)
		{
			ft_print_error(CREATE);
			break ;
		}
	}
	j = -1;
	while (++j < i)
		if (pthread_join(m->philos[j].tid, NULL) != 0)
			return (ft_print_error(JOIN), 1);
	if (pthread_join(m->death, NULL) != 0)
		return (ft_print_error(JOIN), 1);
	return (0);
}

static t_main	*ft_init_main(int argc, char **argv)
{
	t_main	*main;

	if (ft_check_input(argc, argv))
		return (ft_print_error(INV_ARGU), NULL);
	main = (t_main *)malloc(sizeof(t_main));
	if (!main)
		return (ft_print_error(MALLOC), NULL);
	if (!ft_fill_main(argc, argv, main))
		return (NULL);
	return (main);
}

int	main(int argc, char **argv)
{
	t_main		*main;

	if (argc < 5 || argc > 6)
		return (ft_print_error(INV_NUM_ARGU), 1);
	main = ft_init_main(argc, argv);
	if (!main)
		return (1);
	if (ft_threads(main))
		return (ft_clear_end(main), 1);
	ft_clear_end(main);
	return (0);
}
