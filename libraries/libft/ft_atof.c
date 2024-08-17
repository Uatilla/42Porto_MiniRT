/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:44:04 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/17 16:44:10 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	decimal_val(const char *nptr, int i)
{
	float	decimal;
	float	decimal_factor;

	decimal = 0.0f;
	decimal_factor = 0.1f;
	i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		decimal += (nptr[i] - 48) * decimal_factor;
		decimal_factor *= 0.1f;
		i++;
	}
	return (decimal);
}

float	ft_atof(const char *nptr)
{
	int		signal;
	int		i;
	float	number;

	signal = 1;
	number = 0.0f;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signal = signal * (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number *= 10;
		number += nptr[i] - 48;
		i++;
	}
	if (nptr[i] == '.')
		number += decimal_val(nptr, i);
	return (signal * (number));
}
