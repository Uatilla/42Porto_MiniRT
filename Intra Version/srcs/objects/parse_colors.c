/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:17:38 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 20:17:41 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	attribute_pattern(enum e_id type, t_material *obj_mat, char **line)
{
	char		*pattern;
	enum e_p	patt_type;

	set_color(&obj_mat->color_sec, line, type, 'S');
	if (type == PL || type == SP)
		pattern = line[6];
	else if (type == CY || type == CONE)
		pattern = line[8];
	if (!ft_strcmp(pattern, "PC"))
		patt_type = PC;
	else if (!ft_strcmp(pattern, "GR"))
		patt_type = GR;
	else if (!ft_strcmp(pattern, "RNG"))
		patt_type = RNG;
	else if (!ft_strcmp(pattern, "CHK"))
		patt_type = CHK;
	else if (!ft_strcmp(pattern, "DEFAULT"))
		return ;
	obj_mat->pattern = stripe_pattern(&obj_mat->color,
			&obj_mat->color_sec, patt_type);
	obj_mat->pattern.inver = mtx_inverse(NULL, obj_mat->pattern.trans);
}

/// @brief Set the color for the object.
/// @param obj_color tuple from the object structure.
/// @param line Scene line to be used.
/// @param type Type of the object.
/// @param color_type 'P' for Primary or 'S' for Secondary(texture).
void	set_color(t_color *obj_color, char **line,
	enum e_id type, char color_type)
{
	if (color_type == 'P')
	{
		if (type == SP || type == PL)
			fill_tuple(obj_color, line[3], 999999);
		else if (type == CY || type == CONE)
			fill_tuple(obj_color, line[5], 999999);
	}
	else if (color_type == 'S')
	{
		if ((type == SP || type == PL) && count_words(line) > 6)
			fill_tuple(obj_color, line[5], 999999);
		else if ((type == CY || type == CONE) && count_words(line) > 8)
			fill_tuple(obj_color, line[7], 999999);
	}
	obj_color->r = obj_color->r / 255;
	obj_color->g = obj_color->g / 255;
	obj_color->b = obj_color->b / 255;
}
