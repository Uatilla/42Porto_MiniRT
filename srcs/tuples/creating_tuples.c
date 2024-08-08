/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_tuples.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:45:40 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/02 21:01:22 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_tuple	creating_tuple(float x, float y, float z, float w)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}

t_tuple	creating_point(float x, float y, float z)
{
	return (creating_tuple(x, y, z, 1));
}

t_tuple	creating_vector(float x, float y, float z)
{
	return (creating_tuple(x, y, z, 0));
}

t_tuple	creating_color(float r, float g, float b)
{
	return (creating_tuple(r, g, b, 999999));
}
