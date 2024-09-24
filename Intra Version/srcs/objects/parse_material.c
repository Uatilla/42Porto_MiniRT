/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:14:23 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 20:14:26 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_preset2(t_material *m, char *preset)
{
	if (!ft_strcmp("MTL", preset))
	{
		m->ambient = 0.1;
		m->diffuse = 0.3;
		m->shininess = 200;
		m->specular = 0.9;
		m->reflective = 0.7;
	}
	else if (!ft_strcmp("MIR", preset))
	{
		m->ambient = 0.1;
		m->diffuse = 0.7;
		m->shininess = 200;
		m->specular = 0;
		m->reflective = 1.0;
	}
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
	else if (!ft_strcmp("SAT", preset))
	{
		m->ambient = 0.25;
		m->diffuse = 0.5;
		m->shininess = 50;
		m->specular = 0.5;
		m->reflective = 0.5;
	}
	else if (!ft_strcmp("MTL", preset) || !ft_strcmp("MIR", preset))
		set_preset2(m, preset);
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
	m.is_bump = false;
	if (type == SP || type == PL)
	{
		if (count_words(line) > 4)
			preset = line[4];
		else
			preset = "MAT";
		if (count_words(line) > 7)
			m.is_bump = true;
	}
	else if (type == CY || type == CONE)
	{
		if (count_words(line) > 6)
			preset = line[6];
		else
			preset = "MAT";
		if (count_words(line) > 9)
			m.is_bump = true;
	}
	set_preset(&m, preset);
	return (m);
}

/// @brief Set the obj material parameters
/// @param obj Object to have its materials defined.
/// @param m Standard material parameters.
/// @param line Scene line to be used.
/// @param type Type of the object.
void	set_materials(t_shape *sp, t_material *m,
		char **line, enum e_id type)
{
	t_material	*obj_mat;

	obj_mat = &sp->material;
	set_color(&obj_mat->color, line, type, 'P');
	obj_mat->ambient = m->ambient;
	obj_mat->diffuse = m->diffuse;
	obj_mat->specular = m->specular;
	obj_mat->shininess = m->shininess;
	obj_mat->reflective = m->reflective;
	obj_mat->pattern.has = false;
	obj_mat->is_bump = m->is_bump;
	if (type == CY || type == CONE)
		set_cyl_specs(&sp->center, obj_mat, line);
	if (((type == PL || type == SP) && count_words(line) > 6)
		|| ((type == CY || type == CONE) && count_words(line) > 8))
		attribute_pattern(type, obj_mat, line);
}
