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
	fill_tuple(&mrt->input.light.light_pos, line[1], 1);
	mrt->input.light.bright_ratio = ft_atof(line[2]);
	fill_tuple(&mrt->input.light.light_norm_vect, line[2], 999999);
}

/// @brief Just put the camera data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_camera(t_minirt *mrt, char **line)
{
	fill_tuple(&mrt->input.camera.cam_pos, line[1], 1);
	fill_tuple(&mrt->input.camera.cam_norm_vect, line[2], 0);
	mrt->input.camera.fov = ft_atof(line[3]);
}

/// @brief Just put the ambient data into the structure.
/// @param mrt Main structure.
/// @param line Scene line from the file.
void	parse_ambient(t_minirt *mrt, char **line)
{
	mrt->input.ambient.ratio = ft_atof(line[1]);
	fill_tuple(&mrt->input.ambient.color, line[2], 999999);
}
