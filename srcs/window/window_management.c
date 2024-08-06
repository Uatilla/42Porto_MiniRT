/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:17:52 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/05 20:17:53 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*int	close_window(t_minirt *win)
{
	int	line;

	line = win->canvas - 1;
	if (win)
	{
		mlx_destroy_image(win->mlx_ptr, win->map_img.img);
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		mlx_destroy_display(win->mlx_ptr);
		while (line >= 0)
		{
			if (win->map_matrix[line])
				free(win->map_matrix[line]);
			line--;
		}
		free(win->map_matrix);
		free(win->mlx_ptr);
		free(win);
		exit (EXIT_SUCCESS);
	}
	return (0);
}

int	handle_key_event(int key_pressed, void *param)
{
	t_fdf	*win;

	win = (t_fdf *)param;
	if (key_pressed == ESC || !win)
		close_window(win);
	return (0);
}*/