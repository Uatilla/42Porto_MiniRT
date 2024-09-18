/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:00:05 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 20:00:07 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	disp_nothing_selec(void)
{
	printf("\n\tPlease select an element to move/rotate:\n");
	printf("\tUse: 'c' - Camera | 'l' - Light | 'o' - Objects\n");
	printf(" \t\t\t\t\n====================================\n");
}

void	disp_basic_instruc(t_minirt *win)
{
	printf("\t\tMoves: 'up', 'down', 'left', 'right', '+' or '-'.\n");
	if (win->world.scene_elem != LIGHT)
		printf("\t\tRotation: 'w' 'a' 's' 'd' 'q' 'e'.\n");
	printf(" \t\t\t\t\n====================================\n");
}

void	execute_selection(t_minirt *win, int key_pressed)
{
	if (key_pressed == KEY_C)
	{
		win->world.scene_elem = CAMERA;
		printf("\n\tCamera selected.\n");
	}
	else if (key_pressed == KEY_L)
	{
		win->world.scene_elem = LIGHT;
		printf("\n\tLight selected.\n");
	}
	else if (key_pressed == KEY_O)
	{
		win->world.scene_elem = OBJECT;
		printf("\n\tObjects selected.\n");
		printf("\t\tHit TAB to change the object selected.\n");
		printf("\t\tRemove selection: Home (select all objects).\n");
	}
	else if (key_pressed == KEY_HOME)
	{
		win->world.scene_elem = NONE;
		printf("\n\t\tSelection removed.\n");
	}
}

void	disp_advanc_instruc(t_minirt *win)
{
	printf("\n ERROR: COMMAND INVALID!");
	printf("\n\tPlease select an element to move/rotate:\n");
	printf("\t\tUse: 'c' - Camera | 'l' - Light | 'o' - Objects\n");
	printf("\t\tOR,\n");
	printf("\t\tapply modifications on the object already selected:\n\n");
	printf("\t\tMoves: 'up', 'down', 'left', 'right', '+' or '-'\n");
	if (win->world.scene_elem != LIGHT)
		printf("\t\tRotation: 'w' 'a' 's' 'd' 'q' 'e'.\n");
	if (win->world.scene_elem == OBJECT)
	{
		printf("\t\tHit TAB to change the object selected.\n");
		printf("\t\tRemove selection: Home (select all objects)\n");
	}
	printf(" \t\t\t\t\n====================================\n");
}

void	select_scene_elemt(t_minirt *win, int key_pressed)
{
	execute_selection(win, key_pressed);
	if (key_on_scope(key_pressed) && win->world.scene_elem != NONE
		&& !key_on_movement(key_pressed))
		disp_basic_instruc(win);
	if (win->world.scene_elem == NONE)
		disp_nothing_selec();
	if (!key_on_scope(key_pressed) && win->world.scene_elem != NONE)
		disp_advanc_instruc(win);
}
