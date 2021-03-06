/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 04:46:26 by pdeshaye          #+#    #+#             */
/*   Updated: 2021/12/10 04:46:41 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2

char	*ft_strdup(char *src, int n);
int		ft_strchr(const char *string, int searchedChar);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *string, char charset);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif