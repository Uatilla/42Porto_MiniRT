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

// void	clear_ray_inter(t_minirt *data);
//
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

bool	chk_mtx_size(float matrix[4][4], int size)
{
	int	i;
	int	j;
	int chk_row;
	int	chk_col;

	chk_row = 0;
	chk_col = 0;
	i = -1;
	while (matrix[++i])
	{
		j = -1;
		chk_row++;
		chk_col = 0;
		while (matrix[i][++j])
		{
			chk_col++;
			printf("");
		}
		if (chk_col < size)
		{
			printf("Col: %d\n", chk_col);
			return (false);
		}
	}
	if (chk_row < size)
		return (false);
	return (true);
}

int main(void)
{
	float mtx[4][4] = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    };
	if (!chk_mtx_size(mtx, 4))
		printf("False\n");
    return (0);
}
