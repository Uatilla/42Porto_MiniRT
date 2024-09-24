/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:17:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/13 19:38:54 by Jburlama         ###   ########.fr       */
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
enum e_id
{
	A = 0,
	C = 1,
	L = 2,
	SP = 3,
	PL = 4,
	CY = 5,
	CONE = 6,
};

enum e_p
{
	STR = 0,
	PC = 1,
	GR = 2,
	RNG = 3,
	CHK = 4,
};

enum e_sc
{
	NONE = 0,
	LIGHT = 1,
	CAMERA = 2,
	OBJECT = 3,
};

//MACRO
# define EPSILON 0.00001
# define WIDTH 1000
# define HEIGTH 500
# define PI 3.14159

# define KEY_ESC        65307
# define KEY_A          97
# define KEY_C          99
# define KEY_D          100
# define KEY_E			101
# define KEY_L          108
# define KEY_O			111
# define KEY_Q			113
# define KEY_S          115
# define KEY_W          119
# define KEY_LEFT       65361
# define KEY_RIGHT      65363
# define KEY_DOWN       65364
# define KEY_UP         65362
# define KEY_TAB		65289
# define KEY_PLUS       65451
# define KEY_MINUS      65453
# define KEY_HOME       65360
# define KEY_BACK		65288

//STRUCTURES
typedef struct s_checkstx
{
	int		count_a;
	int		count_c;
	int		count_objs;
	int		count_err_stx;
	int		count_err_bump;
	int		count_err_init;
	int		count_preset_err;
	int		count_pattern_err;
	int		count_err_orien_cam;
}	t_checkstx;

typedef struct s_canvas
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_canvas;

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
typedef t_tuple	t_angle;

typedef struct s_matrix
{
	int		rows;
	int		cols;
	float	**mtx;
}	t_matrix;

typedef struct s_xs
{
	int		count;
	float	*arr;
}	t_xs;

typedef struct s_ray
{
	t_point			origin;
	t_vector		direction;
}	t_ray;

typedef struct s_pattern
{
	t_matrix	*trans;
	t_matrix	*inver;
	t_color		a;
	t_color		b;
	enum e_p	type;
	bool		has;
}	t_pattern;

typedef struct s_material
{
	t_pattern	pattern;
	t_color		color;
	t_color		color_sec;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	float		reflective;
	float		min;
	float		max;
	bool		closed;
	bool		is_bump;
}	t_material;

typedef struct s_shape
{
	t_material			material;
	t_ray				trans_ray;
	t_matrix			*mtx_trans;
	t_matrix			*mtx_inver;
	t_point				center;
	t_angle				angle;
	enum e_id			type;
	float				amb_ratio;
	int					id;
	void				*next;
}	t_shape;

typedef t_shape	t_sphere;
typedef t_shape	t_plane;
typedef t_shape	t_cyl;

typedef struct s_intersections
{
	t_point					point;
	t_shape					*obj;
	struct s_intersections	*next;
	float					t[2];
	float					hit;
}	t_intersections;

typedef struct s_comps
{
	t_shape		*obj;
	t_point		point;
	t_point		over_point;
	t_vector	eyev;
	t_vector	normalv;
	t_vector	lightv;
	t_vector	reflectv;
	float		t;
	bool		inside;
	bool		is_shadown;
}	t_comps;

typedef struct s_light
{
	t_point			position;
	t_color			intensity;
	struct s_light	*next;
}	t_light;

typedef struct s_phong
{
	t_color			ambient;
	t_color			diffuse;
	t_color			spec;
}	t_phong;

typedef struct s_cylinder
{
	t_vector			dir;
	enum e_id			type;
	float				min;
	float				max;
	bool				closed;
}	t_cylinder;

typedef struct s_camera
{
	t_matrix	*trans;
	t_matrix	*inver;
	t_point		center;
	t_point		direct_center;
	t_vector	up;
	int			hsize;
	int			vsize;
	float		half_width;
	float		half_height;
	float		pixel_size;
	float		fov;
}	t_camera;

// needs to call ft_memset
typedef struct s_world
{
	t_shape		*objs;
	t_light		*light;
	t_color		ambient_light;
	float		ambient_ratio;
	enum e_sc	scene_elem;
	int			n_objs;
	int			obj_selected;
}	t_world;

typedef struct s_minirt
{
	t_canvas		canvas;
	t_camera		camera;
	t_world			world;
	t_intersections	*inter;
	t_intersections	*first_hit;
	t_tuple			*tuple;	
	int				fd;
	bool			has_color;
}		t_minirt;

typedef struct s_view
{
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_uper;
}	t_view;

// used in ray_for_pixel func
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
float		dot_product(t_tuple *a, t_tuple *b);
float		magnitude(t_tuple *a);
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
t_camera	camera_construct(size_t hsize, size_t vsize, float fov);
t_ray		ray_for_pixel(t_camera *camera, size_t px, size_t py);

//render
//render.c
void		render(t_minirt *data);

// normal
// normal.c
t_vector	normal_at(t_shape *obj, t_point *point, t_minirt *data);
t_vector	local_normal_at(t_shape *obj, t_point *local_point);
t_vector	normal_at_cy(t_point *point, t_shape *obj);
t_vector	normal_at_cone(t_point *point, t_shape *obj);

//computations
//computations.c
t_comps		prepare_computations(t_intersections *i, t_ray *ray, \
			t_minirt *data);
bool		is_shadowed(t_world *w, t_light *light, t_point *p);
t_color		reflected_color(t_comps *comps, t_minirt *data, int8_t remaining);

//light
//light.c
t_color		color_at(t_minirt *data, t_ray *ray, int8_t remainer);
void		point_light(t_point *pos, t_color *intensity, t_world *world);
t_vector	reflect(t_vector *in, t_vector *normal);
t_color		lighting(t_comps *comps, t_light *light, t_world *world);
void		get_specular(t_comps *comps, t_light *light, t_phong *phong);

// light_utils.c
t_color		add_color3(t_color *ambient, t_color *diffuse, t_color *specular);
void		light_is_behind_obj(t_color *diffuse, t_color *specular);
t_color		specular(t_material *material, t_light *light, float refl_dot_eye);
t_color		shade_hit(t_comps *comps, t_world *world, t_minirt *data, \
			int8_t remainer);
void		bump(t_phong *phong, t_shape *obj);

// patterns
// patterns.c
t_pattern	stripe_pattern(t_color *a, t_color *b, enum e_p type);
t_color		point_color(t_point *point);
t_color		stripe_at(t_pattern *patterns, t_point *point);
t_color		gradient(t_pattern *pattern, t_point *point);

//patterns_utils.c
t_color		ring_patt(t_pattern *pattern, t_point *point);
t_color		checker_patt(t_pattern *pattern, t_point *point);
t_color		pattern_at(t_pattern *p, t_point *point, t_shape *obj, \
			enum e_p type);
void		set_pattern(t_intersections *inter, t_point *point);

//objects
//parse_objs.c
void		parse_shape(t_minirt *mrt, enum e_id type, char **line);
void		parse_objects(enum e_id type, t_minirt *data, int file, \
			t_material *m);
void		fill_shape(t_sphere *sp, enum e_id type, char **line, \
			float amb_ratio);
void		set_cyl_specs(t_point *center, t_material *obj, char **line);
void		scale_obj(t_shape *sp, enum e_id type, char **line);
int			count_words(char **line);

//parse_rotation.c
float		find_angle(t_point	reference, t_point p);
void		exec_rotation(t_shape *sp);
void		rotate_obj(t_shape *sp, enum e_id type, char **line);

//parse_settings_utils.c
void		parse_line(t_minirt *mrt, char **line);
void		set_scene(t_minirt *mrt, char *file);
void		fill_tuple(t_tuple *tuple, char *str_tuple, int w);
t_tuple		get_tuple(char *str_tuple, int w);

//parse_render_settings.c
void		parse_ambient(t_minirt *mrt, char **line);
void		parse_camera(t_minirt *mrt, char **line);
void		parse_light(t_minirt *mrt, char **line);
void		set_preset(t_material *m, char *preset);

//parse_material.c
t_material	parse_material(char **line, enum e_id type);
void		set_preset(t_material *m, char *preset);
void		set_materials(t_shape *sp, t_material *m, \
			char **line, enum e_id type);

//parse_colors.c
void		set_color(t_color *obj_color, char **line, enum e_id type, \
			char color_type);
void		attribute_pattern(enum e_id type, t_material *obj_mat, char **line);

//ray
//ray.c
t_tuple		position(t_ray *ray, float t);
t_ray		ray_trasform(t_ray *ray, t_matrix *mtx);

// intersections
// intersections.c
void		ray_intersections(t_minirt *data, t_shape *obj, \
			t_ray *trans_ray, t_ray *ray);
void		intersections(t_minirt *data, t_ray *ray);

// intersections_utils.c
void		first_hit(t_minirt *data);
void		first_inter(t_minirt *data, float *t, t_shape *obj, t_ray *ray);
void		append_inter(t_minirt *data, float *t, t_shape *obj, t_ray *ray);
void		add_intersection(t_minirt *data, float *t, t_shape *obj, \
			t_ray *ray);

//sphere.c
int8_t		ray_sphere_intersect(t_ray *ray, float *t);

//plane.c
int8_t		ray_plane_intersect(t_ray *ray, float *t);

//cylinder.c
int8_t		ray_cylinder_intersect(t_ray *ray, float *t, t_shape *obj);
int8_t		intercections_count(bool *count, float *t);
void		swap(float *t);

//cylinder_cap.c
bool		check_cy_range(t_ray *ray, float t, t_shape *obj);
int8_t		ray_cap_inter(t_ray *ray, float *t, t_shape *obj);
bool		check_cap(t_ray *ray, float t, t_shape *obj, int8_t order);

// cone.c
int8_t		ray_cone_intersect(t_ray *ray, float *t, t_shape *obj);
void		set_cone_intersect(float *a, float *b, float *c, t_ray *ray);

//sort_intersections.c
void		sort_intersections(t_xs	*xs, t_intersections *inter);
void		sort_xs(t_xs *xs);

//map
//map.c
float		map_x(float x, float world_min, float world_max);
float		map_y(float y, float world_min, float world_max);

//Input
//input_checker.c
void		chk_input(t_minirt *mrt, int argc, char *file);
t_checkstx	chk_scene_objs(t_minirt *data, int file);

//input_checker_utils.c
void		check_negative(char *dimension, t_checkstx *chk_stx);
void		check_elemnt(char **line, int elemnt_str, t_checkstx *chk_stx, \
			float *range_limts);
void		check_range(char *val, t_checkstx *chk_stx, float *range_limts);
void		check_dup(char *obj_type, t_checkstx *chk_stx);

//input_chk_render_setup.c
void		input_chk_ambient(t_minirt *mrt, char **line, t_checkstx *chk_stx);
void		input_chk_camera(t_minirt *mrt, char **line, t_checkstx *chk_stx);
void		input_chk_light(t_minirt *mrt, char **line, t_checkstx *chk_stx);
void		check_initials(char *obj_type, t_checkstx *chk_stx);

//input_chk_scene_objs.c
void		input_chk_cyl_con(t_minirt *mrt, char **line, t_checkstx *chk_stx);
void		input_chk_sphere(t_minirt *mrt, char **line, t_checkstx *chk_stx);
void		input_chk_plane(t_minirt *mrt, char **line, t_checkstx *chk_stx);

//input_chk_opt_features.c 
void		check_preset(char *str, t_checkstx *chk_stx);
void		check_pattern(char **line, int n_elem, t_checkstx *chk_stx);
void		check_bump(char **line, int n_elem, t_checkstx *chk_stx);
int			fst_opt_pos(char **line);
int			chk_optional_input(char **line, t_checkstx *chk_stx, \
			int n_elem, int limit);

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

//move_objs.c
void		move_win(t_minirt *win, int key);
void		select_obj(t_minirt *win);
void		move_obj(t_world *world, int key, int obj_selected);
void		execute_move(t_shape *obj, int key);

//move_camera.c
void		move_cam_x(t_camera *camera, int key);
void		move_cam_y(t_camera *camera, int key);
void		move_cam_z(t_camera *camera, int key);
void		move_camera(t_minirt *win, int key);

//rotate_objs.c
void		execute_rotation(t_shape *obj, int key);
void		rotate_obj_running(t_world *world, int key, int obj_selected);
void		rotate_camera(t_minirt *win, int key);
void		rotate_win(t_minirt *win, int key);
void		exec_rotation(t_shape *sp);

//rotate_camera.c
void		rot_cam_z(t_matrix *rotation, t_camera *camera, int key);
void		rot_cam_y(t_matrix *rotation, t_camera *camera, int key);
void		rot_cam_x(t_matrix *rotation, t_camera *camera, int key);
void		rotate_camera(t_minirt *win, int key);

//event_utils.c
void		redo_render(t_minirt *win);
void		select_obj(t_minirt *win);
bool		key_on_scope(int key_pressed);
bool		key_on_movement(int key_pressed);

//handle_hooks.c
void		manage_interface(t_minirt *data);
int			handle_press_key(int key_pressed, void *param);
int			handle_release_key(int key_pressed, t_minirt *data);
int			close_window(t_minirt *win);

//select_elements.c
void		disp_nothing_selec(void);
void		disp_basic_instruc(t_minirt *win);
void		execute_selection(t_minirt *win, int key_pressed);
void		disp_advanc_instruc(t_minirt *win);
void		select_scene_elemt(t_minirt *win, int key_pressed);

//Matrix
//matrix_validations.c
bool		mtx_chk_size(t_matrix *mtx, int rows, int cols);
bool		mtx_size_compare(t_matrix *mtx_a, t_matrix *mtx_b);
bool		mtx_compare(t_matrix *mtx_a, t_matrix *mtx_b);
void		fill_idnty_mtx(t_matrix *mtx);
t_matrix	*mtx_create(t_minirt *data, int rows, int cols);

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

//matrix_transformations.c
void		mtx_rotation_x(t_matrix *mtx, float rot_deg);
void		mtx_rotation_y(t_matrix *mtx, float rot_deg);
void		mtx_rotation_z(t_matrix *mtx, float rot_deg);

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

//mtx_temp.c
//FUNCOES TEMPORARIAS APENAS PARA TESTE!!!!!VVVVVVVVV
void		mtx_fill(t_matrix *mtx);
void		mtx_print(t_matrix *mtx);
//FUNCOES TEMPORARIAS APENAS PARA TESTE!!!!!^^^^^^^^^^^

#endif
