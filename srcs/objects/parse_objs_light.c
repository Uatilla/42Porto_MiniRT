/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:16:54 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/20 19:16:55 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check the syntax of the light.
/// @param line Elements inside Light line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	parse_light(t_minirt *mrt, char **line, t_checkstx *chk_stx)
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