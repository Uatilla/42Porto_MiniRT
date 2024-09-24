/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_chk_render_setup.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:06:21 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/24 15:58:32 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check the syntax of Ambient Element.
/// @param line Elements inside Ambient line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_ambient(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	(void)mrt;
	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_range(line[n_elem], chk_stx, (float []){0.0, 1.0});
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){0.0, 255.0});
	}
	if (n_elem != 3)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of the camera.
/// @param line Elements inside Camera line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_camera(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int			n_elem;
	t_vector	orient;

	(void)mrt;
	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
		{
			if (line[n_elem])
			{
				check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
				orient = get_tuple(line[n_elem], 0);
				if (orient.x == 0 && orient.y == 0 && orient.z == 0)
					chk_stx->count_err_orien_cam++;
			}
		}
		else if (n_elem == 3)
			check_range(line[n_elem], chk_stx, (float []){0.0, 180.0});
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of the light.
/// @param line Elements inside Light line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_light(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	(void)mrt;
	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_range(line[n_elem], chk_stx, (float []){0.0, 1.0});
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}

void	check_initials(char *obj_type, t_checkstx *chk_stx)
{
	if (obj_type)
	{
		if (!ft_strcmp("a", obj_type) || !ft_strcmp("c", obj_type)
			|| !ft_strcmp("l", obj_type))
			chk_stx->count_err_init++;
	}
}
