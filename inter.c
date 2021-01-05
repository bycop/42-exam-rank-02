#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	int	text[256] = {0};
	int i;
	i = -1;
	while (av[1][++i])
		if (text[av[1][i]] == 0)
			text[av[1][i]] = 1;
	i = -1;
	while (av[2][++i])
		if (text[av[2][i]] == 1)
		{	
			text[av[2][i]] = 2;
			write(1, &av[2][i], 1);
		}
	return (0);
}