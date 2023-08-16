#include "get_next_line.h"
#include <stdio.h>

static int	get_one_line(char *buffer, int file)
{
	static int	i = 0;

	while (buffer[i] != '\n' && i < file)
	{
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n");
	i++;
	return (i);
}

void	get_next_line(int fd)
{
	int		BUFFER_SIZE;
	int		file;
	int		count;

	BUFFER_SIZE = 200;
	char	buffer[BUFFER_SIZE];
	count = 0;
	if (fd != -1)
	{
		file = read(fd, buffer, BUFFER_SIZE);
		while (count < file)
		{
			count = get_one_line(buffer, file);
		}
	}
}

int	main(void)
{
	int fd;
	fd = open("teste.txt", O_RDWR);

	get_next_line(fd);
}