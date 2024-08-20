/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:06:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/20 20:06:45 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check the syntax of Sphere Element.
/// @param line Elements inside sphere line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	parse_sphere(t_minirt *mrt, char **line, t_checkstx *chk_stx)
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
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}
