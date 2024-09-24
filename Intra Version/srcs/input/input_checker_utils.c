/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:09:49 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/24 15:58:14 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_char(char *val, t_checkstx *chk_stx)
{
	int	i;
	int	count_dot;
	int	count_minus;
	int	count_plus;

	i = -1;
	count_dot = 0;
	count_minus = 0;
	count_plus = 0;
	while (val[++i])
	{
		if (val[i] < '0' || val[i] > '9')
		{
			if (val[i] == '.')
				count_dot++;
			else if (val[i] == '-')
				count_minus++;
			else if (val[i] == '+')
				count_plus++;
			else
				chk_stx->count_err_stx++;
		}
		if (count_dot > 1 || count_minus > 1 || count_plus > 1)
			chk_stx->count_err_stx++;
	}
}

/// @brief Verify if the element is under the valid value range.
/// @param val Value to be checked.
/// @param chk_stx Temp structure to track syntax errors.
/// @param l_range Lower valid range.
/// @param u_range Upper valid range.
void	check_range(char *val, t_checkstx *chk_stx, float *range_limts)
{
	float	value;

	check_char(val, chk_stx);
	value = ft_atof(val);
	if (value < range_limts[0] || value > range_limts[1])
		chk_stx->count_err_stx++;
}

/// @brief Verify if the string has only three elmnts and is in a valid range.
/// @param line Elements in the line to be checked.
/// @param elemnt_str Element index in line. 
/// @param chk_stx Temp structure to track syntax errors.
/// @param range_limts Float Array limits.
void	check_elemnt(char **line, int elemnt_str, t_checkstx *chk_stx,
		float *range_limts)
{
	int		elemnt;
	char	**rgb_elemts;

	rgb_elemts = ft_split(line[elemnt_str], ',');
	elemnt = -1;
	while (rgb_elemts[++elemnt])
		if (range_limts)
			check_range(rgb_elemts[elemnt], chk_stx, range_limts);
	if (elemnt > 3)
		chk_stx->count_err_stx++;
	free_split(rgb_elemts);
}

/// @brief Verify if the dimension str is a negative float.
/// @param dimension String float do be checked.
/// @param chk_stx Temp structure to track syntax errors.
void	check_negative(char *dimension, t_checkstx *chk_stx)
{
	check_char(dimension, chk_stx);
	if (atof(dimension) < 0.0)
		chk_stx->count_err_stx++;
}

/// @brief Verify if the elements (A, C and L) has duplicates in the Scene.
/// @param obj_type Element type as string.
/// @param chk_stx Temp structure to track syntax errors.
void	check_dup(char *obj_type, t_checkstx *chk_stx)
{
	if (obj_type)
	{
		if (!ft_strcmp(obj_type, "A"))
			chk_stx->count_a++;
		else if (!ft_strcmp(obj_type, "C"))
			chk_stx->count_c++;
	}
}
