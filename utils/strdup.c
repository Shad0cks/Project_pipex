#include "../header.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_strdup(char *src , int n)
{
	char	*cped;
	int	i;

	cped = malloc(sizeof(char) * (ft_min(n , ft_strlen(src)) + 1));
	if (cped == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		cped[i] = src[i];
		i++;
	}
	cped[i] = '\0';
	return (cped);
}