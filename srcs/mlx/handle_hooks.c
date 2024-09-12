/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:47:42 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/04 15:47:44 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	close_window(t_minirt *win)
{
	if (win)
	{
		mlx_destroy_image(win->canvas.mlx, win->canvas.img);
		mlx_destroy_window(win->canvas.mlx, win->canvas.win);
		mlx_destroy_display(win->canvas.mlx);
		free(win->canvas.mlx);
		clean_world(&win->world);
		clean_matrix(win, win->camera.trans, 0);
		clean_matrix(win, win->camera.inver, 0);
		clear_exit(win, 0);
	}
	return (0);
}

void	select_scene_elemt(t_minirt *win, int key_pressed)
{
	if (key_pressed == KEY_C
			|| key_pressed == KEY_L
			|| key_pressed == KEY_O
			|| key_pressed == KEY_HOME)
	{
		if (key_pressed == KEY_C)
			win->world.scene_elem = CAMERA;
		else if (key_pressed == KEY_L)
			win->world.scene_elem = LIGHT;
		else if (key_pressed == KEY_O)
			win->world.scene_elem = OBJECT;
		else if (key_pressed == KEY_HOME)
			win->world.scene_elem = NONE;
	}
	else if (win->world.scene_elem == NONE)
		printf("First select an element to move/rotate:\n\
			Use: 'c' - Camera | 'l' - Light | 'o' - Objects\n");
}

int	handle_press_key(int key_pressed, void *param)
{
	t_minirt	*win;

	win = (t_minirt *)param;
	if (key_pressed == KEY_ESC || !win)
		close_window(win);
	else
	{
		select_scene_elemt(win, key_pressed);
		if (win->world.scene_elem != NONE)
		{
			if (key_pressed == KEY_LEFT
				|| key_pressed == KEY_RIGHT
				|| key_pressed == KEY_DOWN
				|| key_pressed == KEY_UP
				|| key_pressed == KEY_PLUS
				|| key_pressed == KEY_MINUS)
				move_win(win, key_pressed);
			else if (key_pressed == KEY_A
				|| key_pressed == KEY_S
				|| key_pressed == KEY_D
				|| key_pressed == KEY_W)
				printf("Rotate\n");
			else if (key_pressed == KEY_TAB && win->world.scene_elem == OBJECT)
				select_obj(win);
		}
	}
	return (0);
}

int	handle_release_key(int key_pressed, t_minirt *data)
{
	(void)data;
	(void)key_pressed;
	printf("Released\n");
	return (0);
}

void	manage_interface(t_minirt *data)
{
	mlx_hook(data->canvas.win, KeyPress, KeyPressMask, handle_press_key, data);
	mlx_hook(data->canvas.win, KeyRelease, KeyReleaseMask,
		handle_release_key, data);
	mlx_loop(data->canvas.mlx);
}
