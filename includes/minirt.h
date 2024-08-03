/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:17:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/02 21:47:28 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//LIBRARIES
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"

//STRUCTURES

typedef struct	s_canvas {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_canvas;

typedef struct s_tuple
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
			float	w;
		};
		struct
		{
			float	r;
			float	g;
			float 	b;
		};
	};
}	t_tuple;

typedef	t_tuple t_point;
typedef	t_tuple t_vector;
typedef	t_tuple t_color;

typedef	struct	s_ray
{
	t_point		origim;
	t_vector	direction;
}	t_rat;

typedef struct s_minirt
{
	t_tuple     *tuple;
	t_canvas	canvas;
	int			fd;
}		t_minirt;


//MACRO
# define		EPSILON 0.00001
# define		ZERO_TUPLE (t_tuple){{0, 0, 0, 0}}
# define WIDTH 800
# define HEIGTH 600

//FUNCTIONS
//Tuples
//creating_tuples.c
t_tuple creating_tuple(float x, float y, float z, float w);
t_tuple creating_point(float x, float y, float z);
t_tuple creating_vector(float x, float y, float z);
t_tuple creating_color(float r, float g, float b);

//chk_tuples.typ.c
bool    is_point(t_tuple *tuple);
bool    is_vector(t_tuple *tuple);
bool    is_color(t_tuple *tuple);
bool    is_tuple_equal(t_tuple *a, t_tuple *b);

//operations_tuples.c
t_tuple sum_tuples(t_tuple *a, t_tuple *b);
t_tuple subtrac_tuples(t_tuple *a, t_tuple *b);
t_tuple negating_tuple(t_tuple *a);
t_tuple mult_tuple_scalar(t_tuple *a, float sc);
t_tuple div_tuple_scalar(t_tuple *a, float sc);
float dot_product(t_tuple *a, t_tuple *b);
float magnitude(t_tuple *a);

//Input
//input_checker.c
int chk_input(int argc, char *file);

//Exit
//exit_cleaner.c
void    clear_exit(t_minirt *mrt, int status);
void    ft_error(char *msg);

//mlx
//mlx.c
void	start_mlx(t_canvas	*canvas);
void	write_pixel(t_canvas *canvas, int x, int y, t_color *color);
int		map_color(float	c);

#endif
