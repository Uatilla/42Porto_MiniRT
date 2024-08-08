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

t_tuple	lighting(t_material *m, t_light *light, t_point *point, t_vector *eyev, t_vector *normalv);

// nao esquecer de setar a origem da camera(ray) e depois a direcao;
int	main(void)
{
	t_material	material;
	t_point		position = (t_point){0,0,0,1};

	material.color = (t_color){1,1,1,1};
	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;

	t_vector eyev = (t_vector){0, 0, -1, 0};
	t_vector normalv = (t_vector){0, 0, -1, 0};
	t_light	light = set_light(&(t_point){0,0,10,1}, &(t_color){1,1,1,1});

	t_color result = lighting(&material, &light, &position, &eyev, &normalv);

	printf("%f %f %f\n", result.r, result.g, result.b);
}

// int main(void)
// {
// 	t_minirt	data;
// 	t_point		point;
// 	int			x;
// 	int			y;
//
// 	ft_memset(&data, 0, sizeof(data));
// 	parse_objects(SP, &data);
// 	parse_objects(SP, &data);
// 	parse_objects(SP, &data);
// 	parse_objects(SP, &data);
// 	start_mlx(&data.canvas);
// 	data.ray.origin = (t_point){0,0,-5,1};
// 	y = -1;
// 	while (++y < HEIGTH)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			data.ray.first_hit = NULL;
// 			point = (t_point){map_x(x, -5, 5), map_y(y, -5, 5), 10, 1};
// 			check_intersections(&data, &point);
// 			if (data.ray.first_hit)
// 				write_pixel(&data.canvas, x, y, &(t_color){1,0,0,0});
// 			clear_ray_inter(&data);
// 		}
// 	}
// 	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0,0);
// 	mlx_loop(data.canvas.mlx);
// 	clear_exit(&data, 0);
// }
