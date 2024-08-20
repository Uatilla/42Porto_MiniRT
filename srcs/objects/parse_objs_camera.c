/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:56:34 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/20 19:56:36 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check the syntax of the camera.
/// @param line Elements inside Camera line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	parse_camera(t_minirt *mrt, char **line, t_checkstx *chk_stx)
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
			check_range(line[n_elem], chk_stx, (float []){0.0, 180.0});
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}
