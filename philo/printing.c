
#include "philosophers.h"

static int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (0);
	}
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

static int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void	ft_print_num(u_int64_t num)
{
	if (num > 9)
	{
		ft_print_num(num / 10);
		num = num % 10 + 48;
	}
	else
		num += 48;
	write(1, &num, 1);
}

int	ft_print_message(t_philo *p, char *str)
{
	if (!p)
		return (1);
	if (ft_strcmp(str, DIED))
	{
		pthread_mutex_lock(&p->main->print);
		p->main->died = 1;
		ft_print_num((ft_time() - p->main->start_t));
		write(1, " ", 1);
		ft_print_num((u_int64_t)p->num);
		write(1, str, ft_strlen(str));
		return (pthread_mutex_unlock(&p->main->print), 1);
	}
	else
	{
		pthread_mutex_lock(&p->main->print);
		if (p->main->died == 1)
			return (pthread_mutex_unlock(&p->main->print), 1);
		ft_print_num((ft_time() - p->main->start_t));
		write(1, " ", 1);
		ft_print_num((u_int64_t)p->num);
		write(1, str, ft_strlen(str));
		return (pthread_mutex_unlock(&p->main->print), 0);
	}
}

void	ft_print_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}
