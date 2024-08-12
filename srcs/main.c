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

void	mtx_fill_value(t_matrix *mtx)
{
	mtx->mtx[0][0] = -5;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 6;
	mtx->mtx[0][3] = -8;

	mtx->mtx[1][0] = 1;
	mtx->mtx[1][1] = -5;
	mtx->mtx[1][2] = 1;
	mtx->mtx[1][3] = 8;

	mtx->mtx[2][0] = 7;
	mtx->mtx[2][1] = 7;
	mtx->mtx[2][2] = -6;
	mtx->mtx[2][3] = -7;

	mtx->mtx[3][0] = 1;
	mtx->mtx[3][1] = -3;
	mtx->mtx[3][2] = 7;
	mtx->mtx[3][3] = 4;
}

int main(void)
{

	t_minirt	data;
	t_matrix	*mtx_a;
	t_matrix	*mtx_b;
	t_matrix	*mtx_c;


	float	determ_a;
	float	determ_b;

	int			x;
	int			y;
    int rows;
    int cols;

	rows = 4;
	cols = 4;
	ft_memset(&data, 0, sizeof(data));
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	start_mlx(&data.canvas);

	printf("\n=======BEFORE======\n");
	mtx_a = mtx_create(&data, rows, cols);
	mtx_b = mtx_create(&data, rows, cols);
	
	mtx_fill_value(mtx_a);
	mtx_fill(mtx_b);

	mtx_print(mtx_a);
	mtx_print(mtx_b);

	determ_a = determinant(&data, mtx_a);
	printf("Determ A: %f\n", determ_a);

	determ_b = determinant(&data, mtx_b);
	printf("Determ B: %f\n", determ_b);

	mtx_c = mtx_inverse(&data, mtx_a);
	printf("\n=======AFTER======\n");

	clean_matrix(&data, mtx_a, 0);
	clean_matrix(&data, mtx_b, 0);
	if (mtx_c)
	{
		mtx_print(mtx_c);
		clean_matrix(&data, mtx_c, 0);
	}
	

	

	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
    return 0;
}
