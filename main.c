
# include "philo.h"

int main(int  argc, char **argv)
{
	t_gen	gen;

	if (argc < 5 || argc > 6)
		return (1);
	init_gen(&gen, argv);

}
