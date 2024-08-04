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
	t_sphere	sphere = {{0,0,0,1}, 1};
	t_color		color = (t_tuple){1,0,0,9};
	t_inter		inter;

	ft_memset(&data, 0, sizeof(data));
	   data.ray.origin = (t_tuple){{0, 0, -5, 1}};

	inter.object = &sphere;



	start_mlx(&data.canvas);

	for (int y = 0; y < HEIGTH; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			float	xw = map_x(x, -5, 5);
			float	yw = map_y(y, -5, 5);
			t_point	point	= (t_tuple){xw, yw, 10, 1};
			t_vector	ray_to_point = subtrac_tuples(&point, &data.ray.origin);
			
			data.ray.direction = normalize(&ray_to_point);

			inter.count = intersect(&data.ray, &sphere, inter.t);
			if (inter.count == 1 || inter.count == 2)
				write_pixel(&data.canvas, x, y, &color);
			
			// intersections(&data.inter_list, &inter);
		}
	}

	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0,0);
	mlx_loop(data.canvas.mlx);
    return (0);
}
