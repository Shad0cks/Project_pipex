#include "../header.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	index;
	size_t	index_result;

	if (!s)
		return (NULL);
	index_result = 0;
	index = 0;
	result = malloc(ft_min(len, ft_strlen(s)) + 1);
	if (result == NULL)
		return (NULL);
	while (s[index] != '\0')
	{
		if (index >= start && index_result < len)
		{
			result[index_result] = s[index];
			index_result++;
		}
		index++;
	}
	result[index_result] = '\0';
	return (result);
}

static int	count_word(const char *str, char c)
{
	int		i;
	int		trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

char	**ft_split(char const *string, char charset)
{
	size_t		len;
	size_t		index;
	char		**split;

	index = 0;
	if (!string)
		return (NULL);
	split = malloc(((count_word(string, charset)) + 1) * sizeof(*split));
	if (split == NULL)
		return (NULL);
	while (*string != '\0')
	{
		while (*string && *string == charset)
			string++;
		len = 0;
		while (*string && *string != charset)
		{
			string++;
			len++;
		}
		if (*(string - 1) != charset)
			split[index++] = ft_substr(string - len, 0, len);
	}
	split[index] = 0;
	return (split);
}