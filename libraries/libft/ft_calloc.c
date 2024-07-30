/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uatilla <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:30:56 by uatilla           #+#    #+#             */
/*   Updated: 2023/04/21 09:31:06 by uatilla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr_calloc;

	ptr_calloc = malloc(nmemb * size);
	if (!ptr_calloc)
	{
		return (NULL);
	}
	ft_bzero(ptr_calloc, nmemb * size);
	return (ptr_calloc);
}
