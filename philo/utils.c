
#include "philosophers.h"

ssize_t	ft_atoi(char *str)
{
	size_t	num;
	int		i;

	i = 0;
	num = 0;
	if (!str)
		return (-1);
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if ((str[i] && (str[i] < '0' || str[i] > '9')) || num > 2147483647)
		return (-1);
	return (num);
}

int	ft_check_input(int argc, char **argv)
{
	int	i;

	if (!argv)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

u_int64_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(u_int64_t time)
{
	u_int64_t	time2;

	time2 = ft_time();
	while ((ft_time() - time2) < time)
		usleep(time);
}
