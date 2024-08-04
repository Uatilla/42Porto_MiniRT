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
	t_sphere	sphere2 = {{0,0,-5,1}, 1};
	t_inter	inter1;
	t_inter	inter2;

	ft_memset(&data, 0, sizeof(data));

	   data.ray.origin = (t_tuple){{0, 0, -5, 1}};
	data.ray.direction = (t_tuple){{0, 0, 1, 0}};

	inter1.object = &sphere;
	inter1.count = intersect(&data.ray, &sphere, inter1.t);

	intersections(&data.inter_list, &inter1);

	inter2.object = &sphere;
	inter2.count = intersect(&data.ray, &sphere2, inter2.t);

	intersections(&data.inter_list, &inter2);

	for (t_intersections *ptr = data.inter_list; ptr; ptr = ptr->next)
	{
		printf("%hhd\n", ptr->node->count);	
		printf("%f\n", ptr->node->t[0]);	
		printf("%f\n", ptr->node->t[1]);	
		printf("-------------------------\n");
	}

	clear_exit(&data, 0);










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
