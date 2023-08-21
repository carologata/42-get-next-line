#include "get_next_line.h"

int ft_find_newline(char *buffer)
{
	int i;

	i = 0;
	if(buffer == NULL || buffer == 0)
		return (0);
	else
	{
		while(buffer[i] != '\0')
		{
			if(buffer[i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
}

char *ft_get_line(char *big_buffer, int len_line)
{
	int i;
	char *line;

	line = malloc(len_line + 1);

	i = 0;
	while(big_buffer[i] != '\n')
	{
		line[i] = big_buffer[i];
		i++;
	}
	line[i] = '\0';

	return (line);
}

int ft_count_len(char *buffer)
{
	int i;

	i = 0;
	if(buffer == NULL || buffer == 0)
		return (0);
	else
	{
		while(buffer[i] != '\0')
		{
			if(buffer[i] == '\n')
				return (i);
			i++;
		}
		return (i);
	}
}


char *get_next_line(int fd)
{
	// const int BUFFER_SIZE = 3;
	char buffer[BUFFER_SIZE];
	static int characters_read = 1;
	static char *big_buffer;
	int len_line;
	char *line;

	if(characters_read == 0 && (!big_buffer || *big_buffer == 0))
		return (NULL);

	//inicializar o big_buffer com ""
	if(big_buffer == 0)
		big_buffer = ft_strdup("");

	//enquanto não encontrar o '/n' e ainda tiver caracters para ler
	while(ft_find_newline(buffer) == 0  && characters_read != 0)
	{
		characters_read = read(fd, buffer, BUFFER_SIZE);
		if(characters_read < 0)
			return (NULL);
		buffer[characters_read] = '\0';
		big_buffer = ft_strjoin(big_buffer, buffer);
		
		//se characters_read == 0, terminou o arquivo, adicionar o /n
		if(characters_read == 0)
		{
			len_line = ft_count_len(big_buffer);
			big_buffer[len_line] = '\n';
		}
	}

	//calcular o len da line para dar malloc
	len_line = ft_count_len(big_buffer);
	
	//receber o line
	line = ft_get_line(big_buffer, len_line);
	
	//o big_buffer terá o valor restante depois do '/n'
	big_buffer = ft_strchr(big_buffer, '\n');

	//ler os caracteres novamente para quando executar a função ele estiver atualizado
	if(characters_read != 0)
	{
		characters_read = read(fd, buffer, BUFFER_SIZE);
		buffer[characters_read] = '\0';
		if(characters_read != 0)
			big_buffer = ft_strjoin(big_buffer, buffer);
	}

	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd;
	char *res;

	fd = open("teste.txt", O_RDWR);

	//1
	res = get_next_line(fd);
	printf("1: %s\n", res);
	
	//2
	res = get_next_line(fd);
	printf("2: %s\n", res);
	
	//3
	res = get_next_line(fd);
	printf("3: %s\n", res);
	
	//4
	res = get_next_line(fd);
	printf("4: %s\n", res);
	
	//5
	res = get_next_line(fd);
	printf("5: %s\n", res);

	//6
	res = get_next_line(fd);
	printf("6: %s\n", res);

	//7
	res = get_next_line(fd);
	printf("7: %s\n", res);


}