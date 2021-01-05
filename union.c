#include <unistd.h>

int	check(char *str, char c, int i)
{
	int j;

	j = 0;
	while (j < i)
		if (str[j++] == c)
			return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	int i;
	int j;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}

	i = -1;
	while (argv[1][++i])
		if (!check(argv[1], argv[1][i], i))
			write(1, &argv[1][i], 1);
	j = -1;
	while (argv[2][++j])
		if (!check(argv[1], argv[2][j], i) && !check(argv[2], argv[2][j], j))
			write(1, &argv[2][j], 1);
	return (0);
}