/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:17:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 19:13:17 by Jburlama         ###   ########.fr       */
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
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	t_point	center;
	float	radius;
}	t_sphere;

typedef struct s_minirt
{
	t_tuple     *tuple;
	t_canvas	canvas;
	t_ray		ray;
	int			fd;
}		t_minirt;


//MACRO
# define EPSILON 0.00001
# define ZERO_TUPLE (t_tuple){{0, 0, 0, 0}}
# define WIDTH 1000
# define HEIGTH 850

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
float	dot_product(t_tuple *a, t_tuple *b);

//ray
//ray.c
t_tuple	position(t_ray *ray, float t);

//sphere
//sphere.c
int		intersections(t_ray *ray, t_sphere *sphere, float *t);

//map
//map.c
float	map_x(float x, float min, float max);
float	map_y(float y, float min, float max);

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
