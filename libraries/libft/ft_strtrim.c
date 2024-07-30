/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:47:45 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/11 19:58:52 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setcmp(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if ((unsigned char)set[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		j;

	if (!s1 || !*s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_setcmp(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_setcmp(s1[j], set))
		j--;
	if (i > j)
		trimmed = ft_strdup("");
	else
		trimmed = ft_substr(s1, i, j - i + 1);
	return (trimmed);
}
