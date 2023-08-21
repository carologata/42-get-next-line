#include "get_next_line.h"

/* // 1 - ft_strlen
size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

// 2 - ft_strdup
char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// ft_copy_str
char	*ft_copy_str(char const *s1, char const *s2, char *res)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

// 3 - ft_strjoin
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	ft_copy_str(s1, s2, res);
	return (res);
}

// 4 - ft_strchr
char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	u;

	str = (char *)s;
	u = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == u)
		{
			return (&str[i+1]);
		}
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (0);
} */

/////////////////////////////////////////////////////////////////////

char	*ft_get_line(char *big_buffer, int len_line)
{
	int		i;
	char	*line;

	line = malloc(len_line + 1);
	i = 0;
	while (big_buffer[i] != '\n')
	{
		line[i] = big_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	ft_count_len(char *buffer)
{
	int	i;

	i = 0;
	if (buffer == NULL || buffer == 0)
		return (0);
	else
	{
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '\n')
				return (i);
			i++;
		}
		return (i);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	// char		*temp;
	static char	*next_line;
	static int	bytes_read = 1;
	int			len_line;

	// temp = NULL;
	//If there's nothing to read and nothing on next_line, return NULL
	if (bytes_read == 0 && (!next_line || *next_line == 0))
		return (NULL);
	
	//malloc for buffer
	buffer = malloc((BUFFER_SIZE + 1)*sizeof(char));
	
	//Initialize next_line as ""
	if (next_line == 0)
		next_line = ft_strdup("");
	
	//While it has more characters to read and doesn't find '\n'
	while (ft_strchr(buffer, '\n') == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		next_line = ft_strjoin(next_line, buffer);
		//If bytes_read == 0, it's end of file -> add '/n'
		if (bytes_read == 0)
		{
			len_line = ft_count_len(next_line);
			next_line[len_line] = '\n';
		}
	}
	
	//calculate len to malloc
	len_line = ft_count_len(next_line);
	
	//gets the line
	line = ft_get_line(next_line, len_line);
	
	//next_line will save the rest after '/n'
	next_line = ft_strchr(next_line, '\n');
	
	/* if there's more characters to read do this process again, 
	so when the function is called again,
		the value of buffer in the WHILE will be updated */
	if (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			next_line = ft_strjoin(next_line, buffer);

		}
	}
	return (free(buffer), line);
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

	//8
	res = get_next_line(fd);
	printf("8: %s\n", res);
}