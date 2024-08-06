/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:17:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/05 22:05:32 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//LIBRARIES
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <math.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"

// enums
enum e_identifyer
{
	A = 0,
	C = 1,
	L = 2,
	SP = 3,
	PL = 4,
	CY = 5,
};

//STRUCTURES
// (8 * 4) +  (4 * 3) = 44 bytes
typedef struct	s_canvas {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_canvas;

// (4 * 4) = 16 bytes
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

// [4 * 2] + (8 * 3) + 1 = 33 bytes
typedef	struct	s_intersections
{
	float					t[2];
	float					*hit;
	void					*obj;
	struct s_intersections	*next;
	int8_t					count;
}	t_intersections;

// 44 + 44 + (8 * 2) = 104 bytes
typedef	struct	s_ray
{
	t_point			origin;
	t_vector		direction;
	t_intersections	*inter;
	t_intersections	*first_hit;
}	t_ray;

// 44 + 8 + 4 + 4 = 60
typedef struct s_sphere
{
	t_point				center;
	void				*next;
	enum e_identifyer	type;
	float				diameter;
}	t_sphere;

// 104 + 44 + (8 * 2) + 4 = 168 bytes
typedef struct s_minirt
{
	t_ray			ray;
	t_canvas		canvas;
	t_tuple     	*tuple;
	void			*objs;
	int				fd;
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
float	magnitude(t_tuple *a);
t_tuple normalize(t_tuple *a);
t_tuple cross_product(t_tuple *a, t_tuple *b);
t_tuple div_tuple_scalar(t_tuple *a, float sc);

//objects
//parse_objs.c
void	parse_objects(enum e_identifyer type, t_minirt *data);
void	parse_sphere(t_minirt *data);

//ray
//ray.c
t_tuple	position(t_ray *ray, float t);

//sphere
//sphere.c
int8_t	ray_sphere_intersect(t_ray *ray, t_sphere *sphere, float *t);
void	set_hit(t_ray *ray);

//intersections.c
void	ray_intersections(t_minirt *data, void *obj);
void	check_intersections(t_minirt *data, t_point *point);
void	first_inter(t_minirt *data, int8_t point, float *t, t_sphere *obj);
void	append_inter(t_minirt *data, int8_t point, float *t, t_sphere *obj);

//map
//map.c
float	map_x(float x, float world_min, float world_max);
float	map_y(float y, float world_min, float world_max);

//Input
//input_checker.c
int chk_input(int argc, char *file);

//Exit
//exit_cleaner.c
void    clear_exit(t_minirt *mrt, int status);
void    ft_error(char *msg);
void	clear_objs(void	*objs);
void	clear_ray_inter(t_minirt *data);

//mlx
//mlx.c
void	start_mlx(t_canvas	*canvas);
void	write_pixel(t_canvas *canvas, int x, int y, t_color *color);
int		map_color(float	c);

#endif
