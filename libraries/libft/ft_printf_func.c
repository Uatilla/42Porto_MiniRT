/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:36:27 by uviana-a          #+#    #+#             */
/*   Updated: 2023/05/28 15:36:28 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(const char c)
{
	return (write(1, &c, 1));
}

int	ft_hex_base(unsigned long decimal_address, int flag)
{
	int			letter_counter;
	char		*base;

	letter_counter = 0;
	if (flag == 'X')
		base = "0123456789ABCDEF";
	if (flag == 'x')
		base = "0123456789abcdef";
	if (decimal_address >= 16)
	{
		letter_counter += ft_hex_base(decimal_address / 16, flag);
		letter_counter += ft_hex_base(decimal_address % 16, flag);
	}
	else
	{
		letter_counter += ft_putchar(base[decimal_address]);
	}
	return (letter_counter);
}

int	ft_ubase(unsigned int number)
{
	int	letter_counter;

	letter_counter = 0;
	if (number >= 10)
	{
		letter_counter += ft_ubase(number / 10);
		letter_counter += ft_ubase(number % 10);
	}
	else
	{
		letter_counter = ft_putchar("0123456789"[number]);
	}
	return (letter_counter);
}
