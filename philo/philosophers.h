
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILOS 200

# define MALLOC "Malloc failed\n"
# define INIT "Mutex init failed\n"
# define JOIN "Pthread_join failed\n"
# define CREATE "Pthread_create failed\n"
# define INV_ARGU "Please enter only unsigned integers\n"
# define INV_NUM_ARGU "Please use 4 or 5 arguments\n"
# define LOWVAL "Invalid value passed\n"

# define DIED " died\n"
# define FORK " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n" 

struct	s_main;

typedef struct s_philo
{
	int				num;
	pthread_t		tid;
	int				fork_s;
	int				fork_n;
	u_int64_t		d_time;
	int				done;
	pthread_mutex_t	diner;
	pthread_mutex_t	fini;
	struct s_main	*main;
}	t_philo;

typedef struct s_main
{
	int				n_philos;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	u_int64_t		start_t;
	int				died;
	int				rounds;
	int				all_done;
	t_philo			*philos;
	pthread_t		death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	stop;
}	t_main;

//start
int			main(int argc, char *argv[]);
void		*ft_fill_main(int argc, char **argv, t_main *main);

//utils
ssize_t		ft_atoi(char *str);
int			ft_check_input(int argc, char **argv);
u_int64_t	ft_time(void);
int			ft_print_message(t_philo *p, char *str);
void		ft_sleep(u_int64_t time);

//exec
void		*ft_p_thread(void *p_void);

//error_free
void		ft_clear_end(t_main *main);
void		ft_free_philo(t_main *main);
void		ft_free_fork(t_main *main, int i);
void		ft_free_main(t_main *main);
void		ft_free_mutex(t_main *main, int i);
void		ft_print_error(char *str);

#endif
