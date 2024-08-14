/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/08 22:41:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	fill_mtx(t_matrix *mtx)
{
	mtx->mtx[0][0] = 1;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 3;
	mtx->mtx[0][3] = 4;

	mtx->mtx[1][0] = 2;
	mtx->mtx[1][1] = 4;
	mtx->mtx[1][2] = 4;
	mtx->mtx[1][3] = 2;

	mtx->mtx[2][0] = 8;
	mtx->mtx[2][1] = 6;
	mtx->mtx[2][2] = 4;
	mtx->mtx[2][3] = 1;

	mtx->mtx[3][0] = 0;
	mtx->mtx[3][1] = 0;
	mtx->mtx[3][2] = 0;
	mtx->mtx[3][3] = 1;

}


int	main(void)
{
	t_minirt 	data;
	t_light		light;
	int			y;
	int			x;
	float		world_x;
	float		world_y;
	t_vector	eye;
	t_color		color;

	t_matrix	*mtx;
	t_matrix	*mtx_id;
	t_matrix	*mid;
	t_point		p;
	t_point		p2;
	t_point		p3;
	t_point		p4;


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
				light_vec(&data.ray, &light);
				color = lighting(data.ray.first_hit, &light);
				write_pixel(&data.canvas, x, y, &color);
			}
			clear_ray_inter(&data);
		}
	}


	mtx = mtx_create(&data, 4, 4);
	fill_idnty_mtx(mtx);
	mtx_rotation_x(mtx, 90);
	printf("====================\n");

	p = creating_point(1, 0, 1);
	printf("P X:%f Y:%f Z:%f W:%f\n", p.x, p.y, p.z, p.w);
	printf("====================\n");

	p2 = mtx_mult_tuple(mtx, &p);
	printf("P2 X:%f Y:%f Z:%f W:%f\n", p2.x, p2.y, p2.z, p2.w);

	printf("====================\n");
	mtx_id = mtx_create(&data, 4, 4);
	fill_idnty_mtx(mtx_id);
	mtx_scaling(mtx_id, &(t_tuple){5, 5, 5, 1});
	p3 = mtx_mult_tuple(mtx_id, &p2);
	printf("P3 X:%f Y:%f Z:%f W:%f\n", p3.x, p3.y, p3.z, p3.w);

	printf("====================\n");
	mid = mtx_create(&data, 4, 4);
	fill_idnty_mtx(mid);
	mtx_translation(mid, &(t_tuple){10, 5, 7, 1});
	p4 = mtx_mult_tuple(mid, &p3);
	printf("P3 X:%f Y:%f Z:%f W:%f\n", p4.x, p4.y, p4.z, p4.w);



	//mtx_scaling();

	//mtx_translation();

	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
}
