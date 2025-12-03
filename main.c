
# include "philo.h"

int main(int  argc, char **argv)
{
	int		nb;
	t_gen	*gen;
	t_philo *philo;

	if (argc < 5 || argc > 6)
		return (1);
    if (!is_dig_arr(argv))
    {
        printf("parse error\n");
        return ;
    }
    nb = ft_atoi(argv[1]);
    if (nb <= 0)
    {
        printf("insufficient n  of philosophers\n");
        return ;
    }
    gen = malloc(sizeof(t_gen));
    philo = malloc(sizeof(t_philo) * nb);
    init_gen(gen, philo, argv, nb);
	create_threads(&philo, nb);
	clean_exit(gen, nb);
	return (0);

}
