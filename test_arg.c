#include <stdio.h>

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		printf("av[%d]: %s\n", i, av[i]);
		i++;
	}
}
