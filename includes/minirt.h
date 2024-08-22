/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:17:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/22 16:21:08 by Jburlama         ###   ########.fr       */
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
# include "../libraries/minilibx-linux/mlx_int.h"
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

//MACRO
# define EPSILON 0.00001
# define ZERO_TUPLE (t_tuple){0, 0, 0, 0}
# define WIDTH 1000
# define HEIGTH 500
# define BOTH 0
# define FIRST 1
# define SECOND 2
# define ESC 65307
# define PI 3.14159 

//STRUCTURES

typedef struct t_checkstx
{
	int		count_a;
	int		count_c;
	int		count_l;
	int		count_err_stx;
}	t_checkstx;

// (8 * 4) + (4 * 3) = 44 bytes
typedef struct s_canvas
{
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
			float	b;
		};
	};
}	t_tuple;

typedef t_tuple	t_point;
typedef t_tuple	t_vector;
typedef t_tuple	t_color;

// (4 * 2) + 8 = 16 bytes
typedef struct s_matrix
{
	int		rows;
	int		cols;
	float	**mtx;
}	t_matrix;

// 8 + 8 = 16 bytes
typedef struct s_xs
{
	int	count;
	float	*arr;
}	t_xs;

// 16 + [4 * 2] + (8 * 3) + 1 = 49 bytes
typedef	struct	s_intersections
{ 
	t_point					point;
	float					t[2];
	float					hit;
	void					*obj;
	struct s_intersections	*next;
	int8_t					count;
}	t_intersections;

// 16 * 6 = 96 bytes
typedef	struct s_light
{
	t_point	   		position;
	t_color	   		intensity;
	t_vector   		dir;
	t_vector   		reflect;
	t_vector   		eyev;
	t_vector   		normalv;
	struct s_light	*next;
}	t_light;

// 16 * 3 = 32
typedef struct s_phong
{
	t_color			ambient;
	t_color			diffuse;
	t_color 		spec;
} t_phong;

// (16 * 2) = 32 bytes
typedef struct s_ray
{
	t_point			origin;
	t_vector		direction;
}	t_ray;

// 16 + (4 * 4) = 32 bytes
typedef	struct s_material
{
	t_color	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
} t_material;

// 16  + 4 + 4 + 4  + 1 = 29 bytes;
typedef	struct s_cylinder
{
	t_vector			dir;
	enum e_identifyer	type;
	float				min;
	float				max;
	bool				closed;
}	t_cylinder;

// 32 + 16 + (8 * 3) + 4 = 76 bytes
typedef struct s_sphere
{
	t_material			material;
	t_ray				trans_ray;
	t_matrix			*mtx_trans;
	t_matrix			*mtx_inver;
	void				*next;
	enum e_identifyer	type;
}	t_sphere;

// (8 * 2) + (4 * 2) + (4 * 4) = 40 bytes
typedef	struct s_camera
{
	t_matrix	*trans;
	t_matrix	*inver;
	int			hsize;
	int			vsize;
	float		half_width;
	float		half_height;
	float		fov;
	float		pixel_size;
}	t_camera;

// needs to call ft_memset
// (8 * 2) = 16 bytes
typedef	struct	s_world
{
	t_sphere	*sphere;
	t_light		*light;
}	t_world;

// 44 + 40 + 32 + 16 + (8 * 3) + 4 = 160 bytes
typedef struct s_minirt
{
	t_canvas		canvas;
	t_camera		camera;
	t_ray			ray;
	t_xs			xs;
	t_world			world;
	t_intersections	*inter;
	t_intersections	*first_hit;
	t_tuple			*tuple;
	int				fd;
}		t_minirt;

// used in view_transformation func
// (16 * 4) = 64
typedef struct	s_view
{
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_uper;
}	t_view;

// used in ray_for_pixel func
// (4 * 4) = 16 bytes
typedef struct s_rfp
{
	float	xoffset;
	float	yoffset;
	float	w_x;
	float	w_y;
}	t_rfp;

//FUNCTIONS
//Tuples
//creating_tuples.c
t_tuple		creating_tuple(float x, float y, float z, float w);
t_tuple		creating_point(float x, float y, float z);
t_tuple		creating_vector(float x, float y, float z);
t_tuple		creating_color(float r, float g, float b);


//chk_tuples.typ.c
bool		compare_float(float a, float b);
bool		is_point(t_tuple *tuple);
bool		is_vector(t_tuple *tuple);
bool		is_color(t_tuple *tuple);
bool		is_tuple_equal(t_tuple *a, t_tuple *b);

//basic_operations_tuples.c
t_tuple		sum_tuples(t_tuple *a, t_tuple *b);
t_tuple		subtrac_tuples(t_tuple *a, t_tuple *b);
t_tuple		negating_tuple(t_tuple *a);
t_tuple		mult_tuple_scalar(t_tuple *a, float sc);

//operations_tuples.c
t_tuple		sum_tuples(t_tuple *a, t_tuple *b);
t_tuple		subtrac_tuples(t_tuple *a, t_tuple *b);
t_tuple		negating_tuple(t_tuple *a);
t_tuple		mult_tuple_scalar(t_tuple *a, float sc);
float  		dot_product(t_tuple *a, t_tuple *b);
float  		magnitude(t_tuple *a);
t_tuple		normalize(t_tuple *a);
t_tuple		cross_product(t_tuple *a, t_tuple *b);
t_tuple		div_tuple_scalar(t_tuple *a, float sc);
t_color		color_multiply(t_color *c1, t_color *c2);

//view
//view_transformation.c
t_matrix	*view_transformation(t_point *from, t_point *to, t_vector *up);
t_matrix	*view_orientation(t_vector *left, t_vector *up, t_vector *forward);

//camera
//camera.c
t_camera	camera_construct(size_t hsize, size_t vsize, float	fov);
t_ray		ray_for_pixel(t_camera *camera, size_t px, size_t py);

//render
//render.c
void	render(t_minirt *data);

//light
//light.c
void		color_at(t_minirt *data, int x, int y);
void		set_light(t_point *pos, t_color *intensity, t_world *world);
t_vector	normal_at(void *obj, t_point *point, t_minirt *data);
t_vector	reflect(t_vector *in, t_vector *normal);
t_color		lighting(t_intersections *inter, t_light *light);

// light_utils.c
void		light_vec(t_ray *ray, t_light *light, t_minirt *data);
t_color		add_color3(t_color *ambient, t_color *diffuse, t_color *specular);
void		light_is_behind_obj(t_color *diffuse, t_color *specular);
t_color		specular(t_material *material, t_light *light, float refl_dot_eye);

//objects
//parse_objs.c
void		parse_sphere(t_world *world, t_material *m);
void		parse_objects(enum e_identifyer type, t_minirt *data, int file, t_material *m);
void		fill_sphere(t_sphere *sp, t_material *m);
void		set_materials(t_material *obj, t_material *m);

//ray
//ray.c
t_tuple		position(t_ray *ray, float t);
t_ray		ray_trasform(t_ray *ray, t_matrix *mtx);
//
//sphere
//sphere.c
int8_t		ray_sphere_intersect(t_ray *ray, t_sphere *sphere, float *t);

//cylinder
//cylinder.c
int8_t		ray_cylinder_intersect(t_ray *ray, float *t);

//intersections.c
void		ray_intersections(t_minirt *data, void *obj, t_ray *trans_ray);
void		check_intersections(t_minirt *data);
void		first_hit(t_minirt *data);
void   		first_inter(t_minirt *data, int8_t point, float *t, t_sphere *obj);
void   		append_inter(t_minirt *data, int8_t point, float *t, t_sphere *obj);

//sort_intersections.c
void		sort_intersections(t_xs	*xs, t_intersections *inter);
void		sort_xs(t_xs *xs);

//map
//map.c
float		map_x(float x, float world_min, float world_max);
float		map_y(float y, float world_min, float world_max);

//Input
//input_checker.c
int			chk_input(int argc, char *file);

//Exit
//exit_cleaner.c
void		clear_exit(t_minirt *mrt, int status);
void		ft_error(t_minirt *mrt, char *msg, int status);
void		clear_objs(void	*objs);
void		clear_ray_inter(t_minirt *data);
void		clean_matrix(t_minirt *mrt, t_matrix *mtx_struct, int status);

//clean_world.c
void		clean_world(t_world *world);
void		clean_light(t_light *light);
void		clean_sphere(t_sphere *sphere);

//mlx
//mlx.c
void		start_mlx(t_canvas	*canvas);
void		write_pixel(t_canvas *canvas, int x, int y, t_color *color);
int			map_color(float c);
int			close_window(t_minirt *win);
int			handle_key_event(int key_pressed, void *param);

//Matrix
//matrix_validations.c
bool		mtx_chk_size(t_matrix *mtx, int rows, int cols);
bool		mtx_size_compare(t_matrix *mtx_a, t_matrix *mtx_b);
bool		mtx_compare(t_matrix *mtx_a, t_matrix *mtx_b);
void		fill_idnty_mtx(t_matrix *mtx);
t_matrix	*mtx_create(t_minirt *data, int rows, int cols);

//mtx_temp.c
//FUNCOES TEMPORARIAS APENAS PARA TESTE!!!!!VVVVVVVVV
void		mtx_fill(t_matrix *mtx);
void		mtx_print(t_matrix *mtx);
//FUNCOES TEMPORARIAS APENAS PARA TESTE!!!!!^^^^^^^^^^^

//matrix_operations.c
float		get_mtx_value(t_matrix *mtx, int row, int col);
float		mult_mtx_row_col(t_matrix *mtx_a, t_matrix *mtx_b,
				int row, int col);
t_matrix	*mtx_multiply(t_minirt *mrt, t_matrix *mtx_a, t_matrix *mtx_b);
t_tuple		mtx_mult_tuple(t_matrix *mtx_a, t_tuple *tup);
float		mult_mtx_row_tuple(t_matrix *mtx_a, t_tuple *tup, int row);

//matrix_modifications.c
float		determinant(t_minirt *mrt, t_matrix *mtx);
float		minor(t_minirt *mrt, t_matrix *mtx, int row, int col);
t_matrix	*mtx_transpose(t_minirt *mrt, t_matrix *mtx);
t_matrix	*submatrix(t_minirt *mrt, t_matrix *mtx, int excl_row,
				int excl_col);

//matrix_mods_utils.c
void		mtx_translation(t_matrix *mtx, t_tuple *tup_transl);
void		mtx_scaling(t_matrix *mtx, t_tuple *tup_scale);
float		cofactor(t_minirt *mrt, t_matrix *mtx, int row, int col);
t_matrix	*mtx_inverse(t_minirt *mrt, t_matrix *mtx);

//Matrix_transformations
//matrix_transformations.c
float		degree_to_rad(float degree);
void		mtx_rotation_x(t_matrix *mtx, float rot_deg);
void		mtx_rotation_y(t_matrix *mtx, float rot_deg);
void		mtx_rotation_z(t_matrix *mtx, float rot_deg);

#endif
