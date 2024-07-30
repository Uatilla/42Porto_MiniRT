/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:22:26 by uviana-a          #+#    #+#             */
/*   Updated: 2024/01/20 19:22:28 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sep)
			i++;
		if (str[i] != sep && str[i] != '\0')
		{
			count++;
			i++;
		}
		while (str[i] != sep && str[i] != '\0')
			i++;
	}
	return (count);
}
