/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/05 22:09:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clear_objs(void	*objs);

int main(void)
{
	t_minirt	data;
	t_point		point;
	int			x;
	int			y;

	ft_memset(&data, 0, sizeof(data));
	parse_objects(SP, &data);
	start_mlx(&data.canvas);
	data.ray.origin = (t_point){0,0,-5,1};
	y = -1;
	while (++y < HEIGTH)
	{
		x = -1;
		while (++x < WIDTH)
		{
			data.ray.hit = NULL;
			point = (t_point){map_x(x, -5, 5), map_y(y, -5, 5), 10, 1};
			check_intersections(&data, &point);
			ray_intersections(&data.ray, data.objs, &point);
			if (data.ray.hit)
				write_pixel(&data.canvas, x, y, &(t_color){1,0,0,0});
		}
	}
	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0,0);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
}
