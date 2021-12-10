/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 04:43:54 by pdeshaye          #+#    #+#             */
/*   Updated: 2021/12/10 04:44:19 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_strchr(const char *string, int searchedChar)
{
	char	*str;
	int		i;

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
