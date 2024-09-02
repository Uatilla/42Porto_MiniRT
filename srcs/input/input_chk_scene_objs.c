/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_chk_scene_objs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:12:31 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/24 15:12:33 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check if there is the preset indicated is a valid one.
/// @param str Preset string from the input.
/// @param chk_stx Temp structure to track syntax errors.
void	check_preset(char *str, t_checkstx *chk_stx)
{
	if (!ft_strcmp(str, "MAT") || !ft_strcmp(str, "MTL") || !ft_strcmp(str, "SAT"))
		return ;
	chk_stx->count_preset_err++;
}

/// @brief Check the syntax of Sphere Element.
/// @param line Elements inside sphere line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_sphere(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	(void)mrt;
	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_negative(line[n_elem], chk_stx);
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
		else if (n_elem == 4)
			if (line[n_elem])
				check_preset(line[n_elem], chk_stx);
	}
	if (n_elem > 5)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of the plane.
/// @param line Elements inside plane line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_plane(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	(void)mrt;
	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
		else if (n_elem == 4)
			if (line[n_elem])
				check_preset(line[n_elem], chk_stx);
	}
	if (n_elem > 5)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of the cylinder.
/// @param line Elements inside cylinder line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_cylinder(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	(void)mrt;
	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
		else if (n_elem == 3)
			check_negative(line[n_elem], chk_stx);
		else if (n_elem == 4)
			check_negative(line[n_elem], chk_stx);
		else if (n_elem == 5)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
		else if (n_elem == 6)
			if (line[n_elem])
				check_preset(line[n_elem], chk_stx);
	}
	if (n_elem > 7)
		chk_stx->count_err_stx++;
}
