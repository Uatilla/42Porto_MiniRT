/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 19:15:50 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(void)
{
	t_minirt	data;
	// t_color		color = {{1,0,0,0}};
	t_sphere	sphere = {{0,0,0,1}, 1};
	float		t[2];
	t_intersection	inter;

	   data.ray.origin = (t_tuple){{0, 2, -5, 1}};
	data.ray.direction = (t_tuple){{0, 0, 1, 0}};


	inter.object = &sphere;
	inter.count = intersect(&data.ray, &sphere, inter.t);

	printf("%i\n", inter.count);
	printf("%f %f\n", inter.t[0], inter.t[1]);












	// start_mlx(&data.canvas);
	//
	// for (int y = 0; y < HEIGTH; y++)
	// {
	// 	for (int x = 0; x < WIDTH; x++)
	// 	{
	// 		float	xw = map_x(x, -5, 5);
	// 		float	yw = map_y(y, -5, 5);
	//
	// 		if (xw*xw + yw*yw <= sphere.radius)
	// 			write_pixel(&data.canvas, x, y, &color);
	// 	}
	// }
	//
	// mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0,0);
	// mlx_loop(data.canvas.mlx);
    return (0);
}
