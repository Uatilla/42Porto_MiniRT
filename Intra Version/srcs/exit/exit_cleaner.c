/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:30:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/19 16:36:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	clear_exit(t_minirt *mrt, int status)
{
	if (!mrt)
		exit(EXIT_FAILURE);
	exit(status);
}

void	ft_error(t_minirt *mrt, char *msg, int status)
{
	ft_putstr_fd(msg, 2);
	if (status)
		clear_exit(mrt, status);
}

void	clear_ray_inter(t_minirt *data)
{
	t_intersections	*ptr;

	ptr = data->inter;
	while (ptr)
	{
		ptr = ptr->next;
		free(data->inter);
		data->inter = ptr;
	}
	data->first_hit = NULL;
	data->inter = NULL;
}

/// @brief Clean all content of mtx and calls clear_exit if status != 0.
/// @param mrt Main structure.
/// @param mtx_struct Matrix Structure.
/// @param status Error status (If not an error, 0)
void	clean_matrix(t_minirt *mrt, t_matrix *mtx_struct, int status)
{
	int	curr_row;

	curr_row = -1;
	while (++curr_row < mtx_struct->rows)
		free(mtx_struct->mtx[curr_row]);
	if (mtx_struct->mtx)
		free(mtx_struct->mtx);
	if (mtx_struct)
		free(mtx_struct);
	if (status)
		clear_exit(mrt, status);
}
