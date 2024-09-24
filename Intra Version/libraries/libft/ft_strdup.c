/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:38:10 by uviana-a          #+#    #+#             */
/*   Updated: 2023/04/21 13:38:12 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr_strdup;
	size_t	len;

	len = ft_strlen(s) + 1;
	ptr_strdup = malloc(sizeof(char) * len);
	if (!ptr_strdup)
	{
		return (NULL);
	}
	ft_memcpy(ptr_strdup, s, len);
	return (ptr_strdup);
}
