#include "../parsing.h"

static int	function(unsigned int res, int n)
{
	if (res > 4294967295 && n == 1)
		return (-1);
	if (res > 4294967295 && n == -1)
		return (0);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				n;
	int				i;
	unsigned int	res;

	n = 1;
	i = 0;
	res = 0;
	while(str[i] == ' ')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}

	if (str[i] != '\0' && str[i] != '\n' && str[i] != ' ')
		return(-1);
	if ((res > 4294967295 && n == 1) || (res > 4294967295 && n == -1))
		return (function (res, n));
	return (res * n);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	b = (unsigned char *)s2;
	a = (unsigned char *)s1;
	i = 0;
	while ((a[i] || b[i]) && i < n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}