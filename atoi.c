
#include "philo.h"

int ft_atoi(char *s)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	while(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= - 1;
		i++;
	}
	res = 0;
	while(s[i] >= '0' && s[i] <= '9')
	{
	 res = res * 10 + (s[i] - '0'); 
		i++;
	}
	return (res * sign);
}

