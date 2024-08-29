/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:14:37 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/28 20:14:39 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Just put the Sphere data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_sphere(t_minirt *mrt, char **line)
{
	float	sp_diam;

	sp_diam = ft_atof(line[2]);
	get_tuple(&mrt->input.sphere.sp_center, line[1], 1);
	mrt->input.sphere.sp_diam_scale.x = (2 * sp_diam) / 100;
	mrt->input.sphere.sp_diam_scale.y = (2 * sp_diam) / 100;
	mrt->input.sphere.sp_diam_scale.z = (2 * sp_diam) / 100;
	mrt->input.sphere.sp_diam_scale.w = 1;
	get_tuple(&mrt->input.sphere.sp_color, line[3], 999999);
}

/// @brief Just put the Plane data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_plane(t_minirt *mrt, char **line)
{
	get_tuple(&mrt->input.plane.pl_center, line[1], 1);
	get_tuple(&mrt->input.plane.pl_norm_vect, line[2], 0);
	get_tuple(&mrt->input.plane.pl_color, line[3], 999999);
}

/// @brief Just put the Cylinder data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_cylinder(t_minirt *mrt, char **line)
{
	get_tuple(&mrt->input.cylinder.cy_center, line[1], 1);
	get_tuple(&mrt->input.cylinder.cy_norm_vect, line[2], 0);
	mrt->input.cylinder.cy_diam = ft_atof(line[3]);
	mrt->input.cylinder.cy_height = ft_atof(line[4]);
	get_tuple(&mrt->input.cylinder.cy_color, line[5], 999999);
}
