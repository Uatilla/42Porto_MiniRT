/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:16:39 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/03 19:12:16 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * map the x from the window to our world
*/
float	map_x(float x, float min, float max)
{
	return (x * (max - min) / WIDTH - max);
}

/*
 * map the y from the window to our world
*/
float	map_y(float y, float min, float max)
{
	return (y * (max - min) / HEIGTH - max);
}
