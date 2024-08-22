/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs_ambient.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:14:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/20 19:14:29 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	fill_ambient(t_minirt *mrt, char **line)
{
	(void)mrt;
	(void)line;

	printf("FILL AMBIENT\n");
}

/// @brief Check the syntax of Ambient Element.
/// @param line Elements inside Ambient line in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	parse_ambient(t_minirt *mrt, char **line, t_checkstx *chk_stx)
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
	if (chk_stx->count_err_stx == 0)
		fill_ambient(mrt, line);
}
