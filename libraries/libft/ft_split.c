/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:25:57 by uviana-a          #+#    #+#             */
/*   Updated: 2023/04/24 16:25:59 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_strlen_mod(const char *string, char search, int start_index)
{
	int	i;

	i = start_index;
	while (string[i + 1] != search && string[i + 1] != '\0')
	{
		i++;
	}
	return (i);
}

static	int	ft_count_words_v0(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i++;
		}
		else if ((s[i] != c && i == 0) || (s[i] != c && s[i - 1] == c))
		{
			words++;
			i++;
		}
		else
		{
			i++;
		}
	}
	return (words);
}

static	void	ft_fill_split(char const *s, char c, char **ptr_split)
{
	int	i;
	int	j;
	int	start_index;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if ((s[i] != c && i == 0) || (s[i] != c && s[i - 1] == c))
		{
			start_index = i;
			i = ft_strlen_mod(s, c, i);
			ptr_split[j] = ft_substr(s, start_index, (i - start_index + 1));
			j++;
			i++;
		}
	}
	ptr_split[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ptr_split;

	if (!s)
		return (NULL);
	ptr_split = malloc (sizeof(char *) * (ft_count_words_v0(s, c) + 1));
	if (!ptr_split)
		return (NULL);
	ft_fill_split(s, c, ptr_split);
	return (ptr_split);
}
