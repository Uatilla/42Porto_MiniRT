/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/07 21:56:56 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// nao esquecer de setar a origem da camera(ray) e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
int	main(void)
{
	t_minirt 	data;
	t_light		light;
	int			y;
	int			x;
	float		world_x;
	float		world_y;
	t_vector	normal;
	t_vector	eye;
	t_color		color;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);
	parse_objects(SP, &data);
	light = set_light(&(t_point){-10,10,-10,1}, &(t_color){1,1,1,999999});
	data.ray.origin = (t_point){0,0,-5,1};

	y = -1;
	while (++y < HEIGTH)
	{
		x = -1;
		while (++x < WIDTH)
		{
			world_x = map_x(x, -5, 5);
			world_y = map_y(y, -5, 5);
			check_intersections(&data, &(t_point){world_x, world_y, 5, 1});
			if (data.ray.first_hit)
			{
				normal = normal_at((t_sphere *)data.objs, &data.ray.first_hit->point);
				eye = negating_tuple(&data.ray.direction);
				color = lighting(&((t_sphere *)data.objs)->material,
					 			&light, &data.ray.first_hit->point, &eye, &normal);
				write_pixel(&data.canvas, x, y, &color);
			}
			clear_ray_inter(&data);
		}
	}
	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	mlx_loop(data.canvas.mlx);
}
