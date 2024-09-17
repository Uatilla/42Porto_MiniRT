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
		m->reflective = 0;
	}
	else if (!ft_strcmp("MTL", preset))
	{
		m->ambient = 0.1;
		m->diffuse = 0.3;
		m->shininess = 200;
		m->specular = 0.9;
		m->reflective = 0.7;
	}
	else if (!ft_strcmp("SAT", preset))
	{
		m->ambient = 0.25;
		m->diffuse = 0.5;
		m->shininess = 50;
		m->specular = 0.5;
		m->reflective = 0.5;
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
	if (type == SP || type == PL)
	{
		if (line[4])
			preset = line[4];
		else
			preset = "MTL";
	}
	else if (type == CY || type == CONE)
	{
		if (line[6])
			preset = line[6];
		else
			preset = "MTL";
	}
	set_preset(&m, preset);
	return (m);
}
