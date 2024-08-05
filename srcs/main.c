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
	t_sphere	sphere;

	ft_memset(&data, 0, sizeof(data));
	ft_memset(&data, 0, sizeof(sphere));
	data.ray.origin = (t_point){0,0,-5,1};
	sphere.center = (t_point){0,0,0,1};
	start_mlx(&data.canvas);
	for (int y = 0; y < HEIGTH; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			float	t[2];
			float	world_x = map_x(x, -5, 5);	
			float	world_y = map_y(y, -5, 5);
			int8_t	count;
			t_point	point = (t_point){world_x, world_y, 10, 1};
			t_vector point_to_ray = subtrac_tuples(&point, &data.ray.origin);

			data.ray.hit = NULL;
			data.ray.direction = normalize(&point_to_ray);
			count = ray_sphere_intersect(&data.ray, &sphere, t);
			if (count > 0)
			{
				// printf ("%i %i\n", x, y);
				if (data.ray.inter == NULL)
				{
					data.ray.inter = ft_calloc(sizeof(*data.ray.inter), 1);
					data.ray.inter->count = count;
					data.ray.inter->t[0] = t[0];
					data.ray.inter->t[1] = t[1];
					data.ray.inter->obj = SP;
				}
				else
				{
					t_intersections	*temp;

					temp = ft_calloc(sizeof(*temp), 1);
					temp->count = count;
					temp->t[0] = t[0];
					temp->t[1] = t[1];
					temp->obj = SP;
					temp->next = data.ray.inter;
					data.ray.inter = temp;
				}

				if (data.ray.hit == NULL)
				{
					if (data.ray.inter->t[0] > 0)
						data.ray.hit = &data.ray.inter->t[0];
				}
			}
			if (data.ray.hit)
			{
				// printf("%i %i\n", x, y);
				t_color	color = (t_color){1,0,0,0};
				write_pixel(&data.canvas, x, y, &color);
			}
		}
	}

	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	mlx_loop(data.canvas.mlx);
    return (0);
}
