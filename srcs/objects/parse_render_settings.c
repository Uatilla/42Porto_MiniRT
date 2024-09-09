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

/// @brief Define the preset to be used.
/// @param m Attributes inside a t_material structure.
/// @param preset Preset defined as input.
void	set_preset(t_material *m, char *preset)
{
	if (!ft_strcmp("MAT", preset) || !preset)
	{
		m->ambient = 0.3;
		m->diffuse = 0.7;
		m->shininess = 10;
		m->specular = 0.1;
	}
	else if (!ft_strcmp("MTL", preset))
	{
		m->ambient = 0.1;
		m->diffuse = 0.3;
		m->shininess = 200;
		m->specular = 0.9;
	}
	else if (!ft_strcmp("SAT", preset))
	{
		m->ambient = 0.25;
		m->diffuse = 0.5;
		m->shininess = 50;
		m->specular = 0.5;
	}
}

/// @brief Select the preset for each object.
/// @param line Input line to be checked.
/// @param  type Object type.
/// @return Material settings.
t_material	parse_material(char **line, enum e_id type)
{
	t_material	m;
	char		*preset;

	ft_memset(&m, 0, sizeof(t_material));
	if ((type == SP || type == PL) && line[4])
		preset = line[4];
	else if (type == CY && line[5])
		preset = line[5];
	set_preset(&m, preset);
	return (m);
}