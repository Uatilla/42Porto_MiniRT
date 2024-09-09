/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:14:34 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/02 20:50:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * takes as argument the addres of the canvas to initialize the mlx connection
 * canvas->mlx: stabilish a connection with the correct grafical system
 * canvas->win: creates a new window.
 * canvas->img: start a new image.
 * canvas->addr: this will set the address accordingly for each pixel.
*/
void	start_mlx(t_canvas	*canvas)
{
	canvas->mlx = mlx_init();
	canvas->win = mlx_new_window(canvas->mlx, WIDTH, HEIGTH, "MiniRT");
	canvas->img = mlx_new_image(canvas->mlx, WIDTH, HEIGTH);
	canvas->addr = mlx_get_data_addr(canvas->img,
			&canvas->bits_per_pixel, &canvas->line_length, &canvas->endian);
}

/*
 * Arguments:
 * 		pointer to a canvas.
 * 		point x, and y, in the window,
 * 		a tupple color
*/
void	write_pixel(t_canvas *canvas, int x, int y, t_color *color)
{
	char	*pixel;

	pixel = canvas->addr
		+ (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	*(int *)pixel = map_color(color->r) << 16
		| map_color(color->g) << 8 | map_color(color->b);
}

/*
 * map the floating value from 0-1 to a integer 0-255
*/
int	map_color(float c)
{
	if (c <= 0)
		return (0);
	else if (c >= 1)
		return (255);
	else
		return (c * 255);
}

/// @brief Calculates the inverse matrix.
/// @param mrt Main structure.
/// @param mtx Matrix to find the inverse.
/// @return If there is no determinant == NULL, otherwise a new mtx.
t_matrix	*mtx_inverse2(t_minirt *mrt, t_matrix *mtx)
{
	t_matrix	*mtx_res;
	t_matrix	*mtx_trans;
	float		determ;
	int			row;
	int			col;

	determ = determinant(mrt, mtx);
	if (compare_float(determ, 0))
		return (NULL);
	mtx_res = mtx_create(mrt, mtx->rows, mtx->cols);
	if (!mtx_res)
		clean_matrix(mrt, mtx_res, errno);
	row = -1;
	while (++row < mtx->rows)
	{
		col = -1;
		while (++col < mtx->cols)
			mtx_res->mtx[row][col] = cofactor(mrt, mtx, row, col) / determ;
	}
	mtx_trans = mtx_transpose(mrt, mtx_res);
	return (mtx_trans);
}

void	move_win(t_minirt *win, int key)
{
	void	*new_img;
	t_point	obj_center;
	t_shape	*obj;
	
	(void)win;
	//I'm only doing this definition for one object only.
	obj = win->world.objs;
	while (obj)
	{

		obj_center = obj->center;

		//Instead of moving to a specific point, I should keep iterating in a direction, starting
		//from the current center of the object.
		printf("\n");
		if (key == KEY_LEFT)
		{
			printf("LEFT\n");
			obj->center.x = obj_center.x - 1;
		}
		else if (key == KEY_RIGHT)
		{
			printf("RIGHT\n");
			obj->center.x = obj_center.x + 1;
		}
		else if (key == KEY_DOWN)
		{
			printf("DOWN\n");
			obj->center.y = obj_center.y - 1;
		}
		else if (key == KEY_UP)
		{
			printf("UP\n");
			obj->center.y = obj_center.y + 1;
		}
		printf("\n");

		mtx_translation(obj->mtx_trans, &obj->center);
		clean_matrix(NULL, obj->mtx_inver, 0);
		obj->mtx_inver = mtx_inverse(NULL, obj->mtx_trans);
		obj = obj->next;
	}

	//Destroy old Image
	mlx_destroy_image(win->canvas.mlx, win->canvas.img);

	//Start a new image
	win->canvas.img = mlx_new_image(win->canvas.mlx, WIDTH, HEIGTH);
	win->canvas.addr = mlx_get_data_addr(win->canvas.img,
	&win->canvas.bits_per_pixel, &win->canvas.line_length, &win->canvas.endian);
	render(win);
}

