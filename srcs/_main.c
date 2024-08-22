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

void	mtx_fill_a(t_matrix *mtx)
{
	mtx->mtx[0][0] = 1;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 3;
	mtx->mtx[0][3] = 4;

	mtx->mtx[1][0] = 5;
	mtx->mtx[1][1] = 6;
	mtx->mtx[1][2] = 7;
	mtx->mtx[1][3] = 8;

	mtx->mtx[2][0] = 9;
	mtx->mtx[2][1] = 8;
	mtx->mtx[2][2] = 7;
	mtx->mtx[2][3] = 6;

	mtx->mtx[3][0] = 5;
	mtx->mtx[3][1] = 4;
	mtx->mtx[3][2] = 3;
	mtx->mtx[3][3] = 2;
}

void	mtx_fill_b(t_matrix *mtx)
{
	mtx->mtx[0][0] = -2;
	mtx->mtx[0][1] = 1;
	mtx->mtx[0][2] = 2;
	mtx->mtx[0][3] = 3;

	mtx->mtx[1][0] = 3;
	mtx->mtx[1][1] = 2;
	mtx->mtx[1][2] = 1;
	mtx->mtx[1][3] = -1;

	mtx->mtx[2][0] = 4;
	mtx->mtx[2][1] = 3;
	mtx->mtx[2][2] = 6;
	mtx->mtx[2][3] = 5;

	mtx->mtx[3][0] = 1;
	mtx->mtx[3][1] = 2;
	mtx->mtx[3][2] = 7;
	mtx->mtx[3][3] = 8;
}


// nao esquecer de chamar ft_memeset para data;
// nao esquecer de setar a origem da camera(ray) e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
int	main(int argc, char **argv)
{
	t_minirt	data;
	int			x;
	int			y;
	int			fd;
	float		w_x;
	float		w_y;


	ft_memset(&data, 0, sizeof(data));
	fd = chk_input(argc, argv[1]);
	parse_objects(SP, &data, fd);
	mtx_scaling(((t_sphere *)data.objs)->mtx_trans, &(t_point){0.5,0.5,0.5,69});
	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);
	start_mlx(&data.canvas);
	data.ray.origin = (t_point){0, 0, -5, 1};
	y = -1;
	while (++y < HEIGTH)
	{
		x = -1;
		while (++x < WIDTH)
		{
			w_x = map_x(x, -5, 5);		
			w_y = map_y(y, -5, 5);		
			check_intersections(&data, &(t_point){w_x, w_y, 5, 1});
			if (data.first_hit)
			{
				write_pixel(&data.canvas, x, y, &(t_color){1, 0, 0, 69});
			}
			clear_ray_inter(&data);
		}
	}
	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);

		clear_exit(&data, 0);
}
