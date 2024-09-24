/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:02:49 by uviana-a          #+#    #+#             */
/*   Updated: 2023/05/26 16:02:53 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	flag_conversor(char flag, va_list args)
{
	int		letter_counter;
	char	*str;

	letter_counter = 0;
	if (flag == '%')
		letter_counter += ft_putchar('%');
	if (flag == 'c')
		letter_counter += ft_putchar(va_arg(args, int));
	if (flag == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
			letter_counter += ft_putstr("(null)");
		else
			letter_counter += ft_putstr(str);
	}
	if (flag == 'u')
		letter_counter += ft_ubase(va_arg(args, unsigned int));
	if (flag == 'x' || flag == 'X')
		letter_counter += ft_hex_base(va_arg(args, unsigned int), flag);
	return (letter_counter);
}

int	flag_conversor2(char flag, va_list args)
{
	char			*int_converted;
	int				letter_counter;
	unsigned long	point;

	letter_counter = 0;
	if (flag == 'p')
	{
		point = va_arg(args, unsigned long);
		if (point == 0)
			letter_counter += ft_putstr("(nil)");
		else
		{
			letter_counter += ft_putstr("0x");
			letter_counter += ft_hex_base(point, 'x');
		}
	}
	if (flag == 'd' || flag == 'i')
	{
		int_converted = ft_itoa(va_arg(args, int));
		ft_putstr(int_converted);
		letter_counter += ft_strlen(int_converted);
		free(int_converted);
	}
	return (letter_counter);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	const char	*ptr = str;
	int			letter_counter;

	letter_counter = 0;
	va_start(args, str);
	while (*ptr != '\0')
	{
		if (*ptr == '%')
		{
			ptr++;
			if (*ptr == '%' || *ptr == 'c' || *ptr == 's' || *ptr == 'u'
				|| *ptr == 'x' || *ptr == 'X')
				letter_counter += flag_conversor(*ptr, args);
			if (*ptr == 'p' || *ptr == 'd' || *ptr == 'i')
				letter_counter += flag_conversor2(*ptr, args);
		}
		else
			letter_counter += ft_putchar(*ptr);
		ptr++;
	}
	va_end(args);
	return (letter_counter);
}
