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