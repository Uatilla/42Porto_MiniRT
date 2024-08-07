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
	t_matrix	*mtx;
	t_point		point;
	int			x;
	int			y;
    int rows;
    int cols;

	rows = 4;
	cols = 4;
	ft_memset(&data, 0, sizeof(data));
	mtx = creating_matrix(&data, rows, cols);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	start_mlx(&data.canvas);
	fill_mtx(mtx);
	print_mtx(mtx);
	clean_matrix(&data, mtx, 0);

	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
    return 0;
}
