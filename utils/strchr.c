#include "../header.h"

int		ft_strchr(const char *string, int searchedChar)
{
	char	*str;
	int 	i;

	i = 0;
	str = (char *)string;
	while (*str != (char) searchedChar)
	{
		if (*str == '\0')
			return (-1);
		i++;
		str++;
	}
	return (i);
}