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
 * map the x from the window pixel to world coordenates
*/
float	map_x(float x, float world_min, float world_max)
{
	return (x * (world_max - world_min) / WIDTH - world_max);
}

/*
 * map the y from the window pixel to world coordenates
*/
float	map_y(float y, float world_min, float world_max)
{
	return (y * (world_max - world_min) / HEIGTH - world_max);
}
