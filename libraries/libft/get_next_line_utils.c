/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:13:11 by uviana-a          #+#    #+#             */
/*   Updated: 2024/05/20 20:29:14 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_mod(char *s, int c)
{
	char	ch;

	ch = (char)c;
	if (!s)
		return (0);
	while (*s != '\0' && *s != ch)
		s++;
	if (*s == ch)
		return (s);
	return (0);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	join = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1) + \
			ft_strlen_gnl(s2) + 1));
	if (!join)
		return (NULL);
	while (s1[++i] != '\0')
		join[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		join[i++] = s2[j++];
	join[i++] = '\0';
	free(s1);
	return (join);
}
