
#include "philosophers.h"

static int	ft_before_diner_even(t_philo *p)
{
	if (!p)
		return (1);
	pthread_mutex_lock(&p->main->forks[p->fork_n]);
	if (ft_print_message(p, FORK) == 1)
	{
		pthread_mutex_unlock(&p->main->forks[p->fork_n]);
		return (1);
	}
	pthread_mutex_lock(&p->main->forks[p->fork_s]);
	if (ft_print_message(p, FORK) == 1)
	{
		pthread_mutex_unlock(&p->main->forks[p->fork_n]);
		pthread_mutex_unlock(&p->main->forks[p->fork_s]);
		return (1);
	}
	return (0);
}

static int	ft_before_diner(t_philo *p)
{
	if (!p)
		return (1);
	if (p->num != 1 && p->num % 2 == 0)
		return (ft_before_diner_even(p));
	pthread_mutex_lock(&p->main->forks[p->fork_s]);
	if (ft_print_message(p, FORK) == 1)
		return (pthread_mutex_unlock(&p->main->forks[p->fork_s]), 1);
	if (p->main->n_philos == 1)
	{
		ft_sleep(p->main->t_die);
		pthread_mutex_unlock(&p->main->forks[p->fork_s]);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&p->main->forks[p->fork_n]);
		if (ft_print_message(p, FORK) == 1)
		{
			pthread_mutex_unlock(&p->main->forks[p->fork_s]);
			pthread_mutex_unlock(&p->main->forks[p->fork_n]);
			return (1);
		}
	}
	return (0);
}

static int	ft_diner(t_philo *p)
{
	if (!p)
		return (1);
	pthread_mutex_lock(&p->diner);
	if (p->d_time < (ft_time() - p->main->start_t))
	{
		pthread_mutex_unlock(&p->diner);
		pthread_mutex_unlock(&p->main->forks[p->fork_s]);
		return (pthread_mutex_unlock(&p->main->forks[p->fork_n]), 1);
	}
	p->d_time = ft_time() - p->main->start_t + p->main->t_die;
	pthread_mutex_unlock(&p->diner);
	if (ft_print_message(p, EAT) == 1)
	{
		pthread_mutex_unlock(&p->main->forks[p->fork_s]);
		return (pthread_mutex_unlock(&p->main->forks[p->fork_n]), 1);
	}
	ft_sleep(p->main->t_eat);
	if (p->num % 2 == 0)
	{
		pthread_mutex_unlock(&p->main->forks[p->fork_n]);
		return (pthread_mutex_unlock(&p->main->forks[p->fork_s]), 0);
	}
	pthread_mutex_unlock(&p->main->forks[p->fork_s]);
	pthread_mutex_unlock(&p->main->forks[p->fork_n]);
	return (0);
}

static int	ft_check_rounds(t_philo *p)
{
	if (!p)
		return (1);
	pthread_mutex_lock(&p->fini);
	if (p->done < p->main->rounds)
		p->done++;
	if (p->done == p->main->rounds)
	{
		p->done++;
		pthread_mutex_unlock(&p->fini);
		pthread_mutex_lock(&p->main->stop);
		p->main->all_done++;
		if (p->main->all_done == p->main->n_philos)
			return (pthread_mutex_unlock(&p->main->stop), 1);
		pthread_mutex_unlock(&p->main->stop);
	}
	else
	{
		pthread_mutex_unlock(&p->fini);
		pthread_mutex_lock(&p->main->stop);
		if (p->main->all_done == p->main->n_philos)
			return (pthread_mutex_unlock(&p->main->stop), 1);
		pthread_mutex_unlock(&p->main->stop);
	}
	return (0);
}

void	*ft_p_thread(void *p_void)
{
	t_philo	*p;

	p = (t_philo *)p_void;
	if (p->num % 2 == 0)
		ft_sleep(p->main->t_eat + (p->main->n_philos % 2));
	while (1)
	{
		if (ft_before_diner(p))
			break ;
		if (ft_diner(p))
			break ;
		if (p->main->rounds != -1 && ft_check_rounds(p))
			break ;
		if (ft_print_message(p, SLEEP) == 1)
			break ;
		ft_sleep(p->main->t_sleep);
		if (ft_print_message(p, THINK) == 1)
			break ;
	}
	return ((void *)0);
}
