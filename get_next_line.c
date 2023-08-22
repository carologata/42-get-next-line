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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	u;

	str = (unsigned char *)s;
	u = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		str[i] = u;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;
	size_t	size_t_max;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	size_t_max = -1;
	if (size != 0 && (nmemb >= size_t_max / size))
		return (NULL);
	r = malloc(nmemb * size);
	if (r == NULL)
		return (NULL);
	ft_memset(r, 0, nmemb * size);
	return (r);
}

//-------------------------------------------------------------------

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
	line = malloc(len_line + 2);
	i = 0;
	while (next_line[i] != '\0' && next_line[i] != '\n')
	{
		line[i] = next_line[i];
		i++;
	}
	if(next_line[i] == '\n')
	{
		line[i] = '\n';
		line[i+1] = '\0';
	}
	else
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
	while (next_line[i] != '\n' && next_line[i] != '\0')
		i++;
	i++;
	start = i;
	while (next_line[i] != '\0')
		i++;
	len = i - start + 1;
	new_line = ft_calloc(len, 1);
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
	int end_of_file;

	end_of_file = 0;

	if (next_line == 0)
		next_line = ft_strdup("");
	
	buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	while (ft_strchr(buffer, '\n') == 0 && end_of_file == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);

		if(!*next_line && !*buffer && bytes_read == 0)
		{
			free(next_line);
			next_line = 0;
			free(buffer);
			return (NULL);
		}
		if(bytes_read > 0 && bytes_read < BUFFER_SIZE)
		{
			buffer[bytes_read] = '\0';
			end_of_file = 1;
		}	
		else if(bytes_read == BUFFER_SIZE)
			buffer[bytes_read] = '\0';
		else
			break;
		temp = next_line;
		next_line = ft_strjoin(temp, buffer);
		free(temp);
	}

	line = ft_get_line(next_line);
	temp = next_line;
	next_line = ft_get_next_line(temp);
	free(temp);

	// if(end_of_file == 1)
	// 	free(next_line);

	return (free(buffer), line);
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
	printf("1: %s", res);
	free(res);

	//2
	res = get_next_line(fd);
	printf("2: %s", res);
	free(res);

	//3
	res = get_next_line(fd);
	printf("3: %s", res);
	free(res);

	//4
	res = get_next_line(fd);
	printf("4: %s", res);

/* 	//5
	res = get_next_line(fd);
	printf("5: %s", res);

	//6
	res = get_next_line(fd);
	printf("6: %s", res);

	//7
	res = get_next_line(fd);
	printf("7: %s", res);

	//8
	res = get_next_line(fd);
	printf("8: %s", res);

	//9
	res = get_next_line(fd);
	printf("9: %s", res);

	//10
	res = get_next_line(fd);
	printf("10: %s", res); */
}