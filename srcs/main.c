/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/10 21:49:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(void)
{
	t_cylinder	cylinder;
	t_ray		ray;
	int8_t		intercetions;
	float		t[2];
	float		point_of_inter = 0;;
	t_point		point;

	 cylinder.dir = (t_vector){0,1,0,0};
	cylinder.type = CY;
	 cylinder.min = 1;
	 cylinder.max = 2;
	 cylinder.closed = true;

	ray.origin = (t_point){0, 1.5, -2, 1};
	ray.direction = (t_vector){0, 0, 1, 0};

	intercetions = ray_cylinder_intersect(&ray, t);


	if (intercetions > 0)
	{
		if (t[0] < t[1])
			point_of_inter = t[0];
		else
			point_of_inter = t[1];
		point = position(&ray, point_of_inter);
		if (point.y <= cylinder.min)
			intercetions = 0;
		if (point.y >= cylinder.max)
			intercetions = 0;
	}

	if (intercetions == 0)
		printf("no intersections\n");
	else if (intercetions == 1)
		printf("1 intersections\n");
	else if (intercetions == 2)
		printf("2 intersections\n");
	return (0);
}























//nao esquecer de setar a origem da camera(ray) e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
// int	main(void)
// {
// 	t_minirt 	data;
// 	t_light		light;
// 	int			y;
// 	int			x;
// 	float		world_x;
// 	float		world_y;
// 	t_vector	eye;
// 	t_color		color;
//
// 	ft_memset(&data, 0, sizeof(data));
// 	start_mlx(&data.canvas);
// 	parse_objects(SP, &data);
// 	light = set_light(&(t_point){-10,10,-10,1}, &(t_color){1,1,1,999999});
// 	data.ray.origin = (t_point){0,0,-5,1};
//
// 	y = -1;
// 	while (++y < HEIGTH)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			world_x = map_x(x, -5, 5);
// 			world_y = map_y(y, -5, 5);
// 			check_intersections(&data, &(t_point){world_x, world_y, 5, 1});
// 			if (data.ray.first_hit)
// 			{
// 				light_vec(&data.ray, &light);
// 				color = lighting(data.ray.first_hit, &light);
// 				write_pixel(&data.canvas, x, y, &color);
// 			}
// 			clear_ray_inter(&data);
// 		}
// 	}
// 	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
// 	mlx_loop(data.canvas.mlx);
// }
