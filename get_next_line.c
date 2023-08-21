#include "get_next_line.h"

// 1 - ft_strlen
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
}

int	ft_count_len(char *next_line)
{
	int i;

	i = 0;
	if (next_line == NULL || next_line == 0)
		return (0);
	else
	{
		while (next_line[i] != '\0')
		{
			if (next_line[i] == '\n')
				return (i);
			i++;
		}
		return (i);
	}
}
char	*ft_get_line(char *next_line)
{
	int		i;
	char	*line;
	int		len_line;

	len_line = ft_count_len(next_line);
	line = malloc(len_line + 1);
	i = 0;
	while (next_line[i] != '\n')
	{
		line[i] = next_line[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_next_line(char *next_line)
{
	int		i;
	int		start;
	int		len;
	char	*new_line;

	i = 0;
	len = 0;
	while (next_line[i] != '\n')
		i++;
	i++;
	start = i;
	while (next_line[i] != '\0')
		i++;
	len = i - start + 1;
	new_line = malloc(len * sizeof(char));
	i = 0;
	while (i < len - 1)
	{
		new_line[i] = next_line[start];
		i++;
		start++;
	}
	return (new_line);
}

#include <stdio.h>
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*next_line;
	char		*temp;
	char		*line;
	int			bytes_read;
	int len_line;

	if (next_line == 0)
		next_line = ft_strdup("");
	
	buffer = malloc(BUFFER_SIZE + 1);
	while (ft_strchr(buffer, '\n') == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// if (bytes_read == 0)
		// {
		// 	len_line = ft_count_len(next_line);
		// 	next_line[len_line] = '\n';
		// 	buffer[bytes_read] = '\n';
		// }

		buffer[bytes_read] = '\0';
		temp = next_line;
		next_line = ft_strjoin(temp, buffer);
		free(temp);
	}

	line = ft_get_line(next_line);
	next_line = ft_get_next_line(next_line);

	return (line);
}

#include <fcntl.h>
#include <stdio.h>

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