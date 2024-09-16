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
		clean_matrix(win, win->camera.trans, 0);
		clean_matrix(win, win->camera.inver, 0);
		mlx_destroy_image(win->canvas.mlx, win->canvas.img);
		mlx_destroy_window(win->canvas.mlx, win->canvas.win);
		mlx_destroy_display(win->canvas.mlx);
		free(win->canvas.mlx);
		clean_world(&win->world);
		printf("Bye\n");
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
		{
			win->world.scene_elem = CAMERA;
			printf("\t\tCamera selected.\n");
		}
		else if (key_pressed == KEY_L)
		{
			win->world.scene_elem = LIGHT;
			printf("\t\tLight selected.\n");
		}
		else if (key_pressed == KEY_O)
		{
			win->world.scene_elem = OBJECT;
			printf("\t\tObjects selected.\n");
			printf("\t\tYou can use TAB to change the object selected.\n");
		}
		else if (key_pressed == KEY_HOME)
		{
			win->world.scene_elem = NONE;
			printf("\t\tSelection removed\n");
		}
		if (win->world.scene_elem != NONE)
			printf("\t\tUse A W S D or arrow up, arrow down, +... Or click home remove selection\n");
	}
	else if (win->world.scene_elem == NONE)
		printf("\t\tSelect an element to move/rotate:\n\
			Use: 'c' - Camera | 'l' - Light | 'o' - Objects\n");
	else if (key_pressed != KEY_LEFT && key_pressed != KEY_RIGHT
				&& key_pressed != KEY_DOWN && key_pressed != KEY_UP
				&& key_pressed != KEY_PLUS && key_pressed != KEY_MINUS
				&& key_pressed != KEY_W && key_pressed != KEY_A
				&& key_pressed != KEY_S && key_pressed != KEY_D
				&& key_pressed != KEY_E && key_pressed != KEY_Q)
				printf("\t\tSelect an element to move/rotate:\n\
			Use: 'c' - Camera | 'l' - Light | 'o' - Objects\n\
			OR\n\t\tUse A W S D or arrow up, arrow down, +... to move the current selection Or click home remove selection\n");
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
			if (key_pressed == KEY_LEFT || key_pressed == KEY_RIGHT
				|| key_pressed == KEY_DOWN || key_pressed == KEY_UP
				|| key_pressed == KEY_PLUS || key_pressed == KEY_MINUS)
				move_win(win, key_pressed);
			else if (key_pressed == KEY_W || key_pressed == KEY_A
				|| key_pressed == KEY_S || key_pressed == KEY_D
				|| key_pressed == KEY_E || key_pressed == KEY_Q)
				rotate_win(win, key_pressed);
			if (key_pressed == KEY_TAB)
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
	mlx_put_image_to_window(data->canvas.mlx, data->canvas.win, data->canvas.img, 0, 0);
	mlx_hook(data->canvas.win, 17, 0L, close_window, data);
	mlx_hook(data->canvas.win, KeyPress, KeyPressMask, handle_press_key, data);
	mlx_loop(data->canvas.mlx);
}
