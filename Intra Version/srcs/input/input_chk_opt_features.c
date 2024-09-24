/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_chk_opt_features.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:52:18 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 16:52:21 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check if there is the preset indicated is a valid one.
/// @param str Preset string from the input.
/// @param chk_stx Temp structure to track syntax errors.
void	check_preset(char *str, t_checkstx *chk_stx)
{
	if (!ft_strcmp(str, "MAT") || !ft_strcmp(str, "MTL")
		|| !ft_strcmp(str, "SAT") || !ft_strcmp(str, "MIR"))
		;
	else
		chk_stx->count_preset_err++;
}

void	check_pattern(char **line, int n_elem, t_checkstx *chk_stx)
{
	check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
	if (line[++n_elem] && (!ft_strcmp(line[n_elem], "PC")
			|| !ft_strcmp(line[n_elem], "GR") || !ft_strcmp(line[n_elem], "RNG")
			|| !ft_strcmp(line[n_elem], "CHK")))
		;
	else if (!ft_strcmp(line[n_elem], "DEFAULT"))
		;
	else
		chk_stx->count_pattern_err++;
}

void	check_bump(char **line, int n_elem, t_checkstx *chk_stx)
{
	if (!ft_strcmp(line[n_elem], "BUMP"))
		;
	else
		chk_stx->count_err_bump++;
}

int	fst_opt_pos(char **line)
{
	if (!ft_strcmp(line[0], "sp") || !ft_strcmp(line[0], "pl"))
		return (4);
	else
		return (6);
}

int	chk_optional_input(char **line, t_checkstx *chk_stx, int n_elem, int limit)
{
	int	base;

	base = fst_opt_pos(line);
	while (line[++n_elem])
	{
		if (line[n_elem] && (n_elem - base == 0))
			check_preset(line[n_elem], chk_stx);
		else if (line[n_elem] && (n_elem - base == 1))
		{
			limit += 2;
			check_pattern(line, n_elem, chk_stx);
		}
		else if (line[n_elem] && (n_elem - base == 3))
		{
			limit++;
			check_bump(line, n_elem, chk_stx);
		}
	}
	return (limit);
}
