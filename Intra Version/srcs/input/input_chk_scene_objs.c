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

/// @brief Check the syntax of Sphere Element.
/// @param line Elements inside sphere line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_sphere(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;
	int	limit;

	(void)mrt;
	n_elem = -1;
	limit = 5;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_negative(line[n_elem], chk_stx);
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
		else if (n_elem == 4)
			break ;
	}
	limit = chk_optional_input(line, chk_stx, --n_elem, limit);
	if (n_elem > limit)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of the plane.
/// @param line Elements inside plane line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_plane(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int	n_elem;
	int	limit;

	(void)mrt;
	n_elem = -1;
	limit = 5;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
		else if (n_elem == 4)
			break ;
	}
	limit = chk_optional_input(line, chk_stx, --n_elem, limit);
	if (n_elem > limit)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of the cylinder.
/// @param line Elements inside cylinder line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	input_chk_cyl_con(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	int		n_elem;
	int		limit;

	(void)mrt;
	n_elem = -1;
	limit = 7;
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
			break ;
	}
	limit = chk_optional_input(line, chk_stx, --n_elem, limit);
	if (n_elem > limit)
		chk_stx->count_err_stx++;
}
