
#include  "philo.h"

int is_digit(char *s)
{
	int i;
	int len;

	len = 0;
	while(s[len])
		len++;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i == len)
		return (1);
	return (0);
}

int is_dig_arr(char **s)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		if (!is_digit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
