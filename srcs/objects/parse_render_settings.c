/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_render_settings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:13:26 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/28 20:13:28 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Just put the Light data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_light(t_minirt *mrt, char **line)
{
	t_point	light_point;
	t_color	light_color;
	float	light_intens;

	light_point = get_tuple(line[1], 1);
	light_intens = ft_atof(line[2]);
	light_color = get_tuple(line[3], 999999);
	light_color.r = light_intens * (light_color.r / 255);
	light_color.g = light_intens * (light_color.g / 255);
	light_color.b = light_intens * (light_color.b / 255);
	point_light(&light_point, &light_color, &mrt->world);
}

/// @brief Just put the camera data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_camera(t_minirt *mrt, char **line)
{
	mrt->camera = camera_construct(WIDTH, HEIGTH,
			degree_to_rad(ft_atof(line[3])));
	mrt->camera.center = get_tuple(line[1], 1);
	mrt->camera.direct_center = (t_point){0, 0, 0, 1};
	mrt->camera.up = get_tuple(line[2], 0);
	mrt->camera.trans = view_transformation(&mrt->camera.center,
			&mrt->camera.direct_center, &mrt->camera.up);
	mrt->camera.inver = mtx_inverse(mrt, mrt->camera.trans);
}

/// @brief Just put the ambient data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_ambient(t_minirt *mrt, char **line)
{
	mrt->world.ambient_light = get_tuple(line[2], 999999);
	mrt->world.ambient_ratio = ft_atof(line[1]);
}
