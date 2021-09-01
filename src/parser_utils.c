#include "../includes/so_long.h"

void	open_file(int *fd, char *fname, int opt)
{
	if (opt == 0)
		*fd = open(fname, O_RDONLY);
	if (*fd < 3)
	{
		printf("Error reading the file\n");
		exit(0);
	}
}

int	width_map(int *width, char *buffer, int *counter)
{
	int	i;

	i = 0;
	while (buffer[i] != '\n')
	{
		(*width)++;
		i++;
	}
	*counter = 1;
	return (i);
}
