/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:36:28 by amaula            #+#    #+#             */
/*   Updated: 2025/02/27 15:42:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* Defines */
# define EPSILON 0.001
# define BACKGROUND_COLOR 0x000000ff
# define FAILURE 1
# define SUCCESS 0
# define HIT 1
# define NO_HIT 0
# define SHINE 32.0
# define HAS_COLOR 0
# define SPEC 0

/* Dimensions of the image_plane and initial window size */
# define X 1000
# define Y 1000

/* Number of times a ray reflects off a surface */
# define REFLECTIONS 0

/*	How reflective each surface is in range [0,1]
	0 = not reflective at all
	1 = completely reflective */
# define REFLECTIVITY 0

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <float.h>
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>

/* Enums */

/**
 * e_type - Enum representing different object types in the scene.
 *
 * Members:
 * - CAMERA: Represents the camera object.
 * - LIGHT: Represents a light source.
 * - AMBIENT: Represents ambient light.
 * - SPHERE: Represents a sphere object.
 * - PLANE: Represents a plane object.
 * - CYLINDER: Represents a cylinder object.
 * - NONE: Represents an uninitialized or unknown object.
 */
typedef enum e_type
{
	CAMERA,
	LIGHT,
	AMBIENT,
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}	t_type;

/*Structs*/

/**
 * s_vector - Struct representing a 3D vector.
 *
 * Members:
 * - x: X-coordinate of the vector.
 * - y: Y-coordinate of the vector.
 * - z: Z-coordinate of the vector.
 */
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

/**
 * s_ray - Struct representing a ray in 3D space.
 *
 * Members:
 * - direction: Direction vector of the ray.
 * - coll_norm: Normal vector at the collision point.
 * - end: End position of the ray (collision point if applicable).
 * - start: Starting position of the ray.
 * - distance: Distance traveled by the ray.
 * - color: The color associated with the ray.
 * - object: Pointer to the object the ray intersects with.
 */
typedef struct s_ray
{
	t_vector		direction;
	t_vector		coll_norm;
	t_vector		end;
	t_vector		start;
	double			distance;
	uint32_t		color;
	struct s_object	*object;
}	t_ray;

/**
 * s_image_plane - Struct representing the image plane used for rendering.
 *
 * Members:
 * - view_distance: Distance from the camera to the image plane.
 * - u: Horizontal axis vector of the image plane.
 * - v: Vertical axis vector of the image plane.
 * - ray: Ray associated with the pixel being traced.
 */
typedef struct s_image_plane
{
	double		view_distance;
	t_vector	u;
	t_vector	v;
	t_ray		ray;
}	t_image_plane;

/**
 * s_object - Struct representing an object in the scene.
 *
 * Members:
 * - type: Type of the object (e.g., SPHERE, PLANE, etc.).
 * - color: The color of the object.
 * - diameter: Diameter of the object (if applicable).
 * - height: Height of the object (if applicable).
 * - brightness: Brightness of the object (relevant for lights).
 * - location: Position of the object in 3D space.
 * - orientation: Direction or normal vector (for planes and cylinders).
 * - collisionf: Function pointer for handling ray-object collisions.
 * - print_object: Function pointer for printing object details.
 * - fov: Field of view (relevant for cameras).
 */
typedef struct s_object
{
	t_type		type;
	uint32_t	color;
	double		diameter;
	double		height;
	double		brightness;
	t_vector	location;
	t_vector	orientation;
	int			(*collisionf)(t_ray *, struct s_object *);
	void		(*print_object)(struct s_object *);
	int			fov;
}	t_object;

/**
 * s_ambient - Struct representing ambient lighting in the scene.
 *
 * Members:
 * - obj: Pointer to the ambient light object.
 * - color: The color of the ambient light.
 */
typedef struct s_ambient
{
	t_object	*obj;
	t_vector	color;
}	t_ambient;

/**
 * s_light - Struct representing a light source.
 *
 * Members:
 * - obj: Pointer to the light object.
 * - light_dir: Direction of the light.
 * - view_dir: Direction from the surface point to the viewer.
 * - diffuse: Diffuse lighting intensity.
 * - specular: Specular lighting intensity.
 * - shine: Shininess factor for specular highlights.
 * - color: Final computed color of the light contribution.
 * - r: Red component of the light color.
 * - g: Green component of the light color.
 * - b: Blue component of the light color.
 */
typedef struct s_light
{
	t_object	*obj;
	t_vector	light_dir;
	t_vector	view_dir;
	double		diff;
	double		spec;
	double		shine;
	uint32_t	color;
	int			r;
	int			g;
	int			b;
}	t_light;

/**
 * s_objarr - Struct representing an array of objects in the scene.
 *
 * Members:
 * - arr: Pointer to an array of objects.
 * - capacity: Maximum number of objects that can be stored.
 * - objects: Current number of objects in the array.
 */
typedef struct s_objarr
{
	t_object	*arr;
	size_t		capacity;
	size_t		objects;
}	t_objarr;

/**
 * s_mouse - Struct representing the state of the mouse.
 *
 * Members:
 * - x: X-coordinate of the mouse position.
 * - y: Y-coordinate of the mouse position.
 * - left: Boolean flag indicating if the left button is pressed.
 * - right: Boolean flag indicating if the right button is pressed.
 */
typedef struct s_mouse
{
	int32_t	x;
	int32_t	y;
	int		left;
	int		right;
}	t_mouse;

/**
 * s_data - Struct holding all the necessary data for the ray tracing engine.
 *
 * Members:
 * - objects: Pointer to an array of objects in the scene.
 * - camera: Pointer to the camera object.
 * - light: Pointer to the light source.
 * - ambient: Pointer to the ambient lighting settings.
 * - info: Image plane data for rendering.
 * - selected: Pointer to the currently selected object.
 * - mlx: Pointer to the MLX instance for rendering.
 * - image: Pointer to the rendered image.
 * - mouse: Struct containing mouse state information.
 * - file: Pointer to the file containing the scene description.
 */
typedef struct s_data
{
	t_objarr		*objects;
	t_object		*camera;
	t_light			*light;
	t_ambient		*ambient;
	t_image_plane	info;
	t_object		*selected;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_mouse			mouse;
	char			*file;
}	t_data;

/**
 * s_disc - Struct representing the discriminant for quadratic equations.
 *
 * Members:
 * - a: Quadratic coefficient a.
 * - b: Quadratic coefficient b.
 * - c: Quadratic coefficient c.
 * - discriminant: The computed discriminant value (b² - 4ac).
 */
typedef struct s_disc
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
}	t_disc;

/**
 * s_cylinder_coll - Struct representing collision data for a cylinder.
 *
 * Members:
 * - proj_dir: Projection of the ray direction onto the cylinder's axis.
 * - oc_proj: Projection of the ray origin onto the cylinder's axis.
 * - oc: Vector from the cylinder's base to the ray origin.
 * - coll_point: Collision point on the cylinder.
 * - height_proj: Projection of the collision height on the cylinder axis.
 */
typedef struct s_cylinder_coll
{
	t_vector	proj_dir;
	t_vector	oc_proj;
	t_vector	oc;
	t_vector	coll_point;
	double		height_proj;
}	t_cylinder_coll;

/**
 * s_cap_collision - Struct representing collision data for cylinder caps.
 *
 * Members:
 * - center: Center of the cap.
 * - cap_normal: Normal vector of the cap.
 * - collision: Collision point on the cap.
 * - t: Distance along the ray where the collision occurs.
 * - denom: Denominator in the intersection equation (dot product check).
 */
typedef struct s_cap_collision
{
	t_vector	center;
	t_vector	cap_normal;
	t_vector	collision;
	double		t;
	double		denom;
}	t_cap_collision;

/*camera.c*/

void			camera_checks(int (**checks)(char *));
int				assign_camera(t_object *camera, char **info);
void			print_camera(t_object *camera);

/*collision.c*/

int				sphere_collision(t_ray *ray, t_object *sp);
int				plane_collision(t_ray *ray, t_object *pl);
int				cylinder_collision(t_ray *ray, t_object *cy);

/*collision utils.c*/

t_vector		compute_normal_curved(t_vector collision_point, t_object *cy);
void			update_ray(t_ray *ray, t_object *object, double t);
double			calc_t(double *t, t_vector v1, t_vector v2, double r);

/*color.c*/

uint32_t		mix_colors(uint32_t c1, uint32_t c2, double reflectivity);
void			light_col(t_data *d, t_ray *ray, t_vector *f_col, double s_f);
void			color_pixel(mlx_image_t *i, uint32_t pixel_c, int x, int y);
t_vector		decompose_color(uint32_t color);
uint32_t		recompose_color(t_vector color);

/*cylinder.c*/

void			cylinder_checks(int (**checks)(char *));
int				assign_cylinder(t_object *cylinder, char **info);
void			print_cylinder(t_object *c);

/*data*/

t_data			*init_data(char *file);
void			free_data(t_data *data);

/*errors.c*/

int				failure(char *message);
void			error_msg(t_data *data);

/*file_reader.c*/

int				read_objects(t_data *data);

/*image.c*/

void			redraw(t_data *data);
void			reset_scene(t_data *data);

/*keyhandler.c*/

void			keypress(mlx_key_data_t mlx_data, void *param);

/*keyhandler2.c*/

int				change_fov(mlx_key_data_t mlx_data, t_object *selected);
int				adjust_brightness(mlx_key_data_t mlx_data, t_object *selected);
int				resize_object(mlx_key_data_t mlx_data, t_object *selected);

/*lights.c*/

void			ambient_checks(int (**checks)(char *));
void			lights_checks(int (**checks)(char *));
uint32_t		set_lights(t_data *d, t_ray *r, t_vector coll);

/*light_utils.c*/

double			in_the_shadow(t_ray *ray, t_object *light, t_data *data);
double			set_specular(t_vector norm, t_light *light);
double			set_diffuse(t_vector normal, t_light *light);
void			print_light(t_object *l);
void			print_ambient(t_object *a);

/*mouse.c*/

void			rt_mouse(void *param);

/*object.c*/

t_type			get_type(char *line);
int				parse_object(t_object *object, char *line);

/*object_array.c*/

t_objarr		*init_objarr(size_t capacity);
int				add_object(t_data *data, char *line);
void			free_objarr(t_objarr *objarr);

/*parser.c*/

t_vector		parse_vector(char *str);
uint32_t		parse_color(char *str);
double			parse_double(char *str);

/*plane.c*/

void			plane_checks(int (**checks)(char *));
int				assign_plane(t_object *plane, char **info);
void			print_plane(t_object *p);

/*precalculations.c*/

t_image_plane	image_plane(t_object *camera);
void			set_precalculations(t_data *data);

/*printer.c*/

void			print_objects(t_data *data);
void			print_vector(t_vector v);
void			print_help(void);
void			print_color(uint32_t color);

/*ray.c*/

int				cast_ray(t_ray *ray, t_data *data, int reflections);
void			raycast(t_data *data);
t_ray			get_ray(t_image_plane info, int x, int y);

/*sphere.c*/

void			sphere_checks(int (**checks)(char *));
int				assign_sphere(t_object *sphere, char **info);
void			print_sphere(t_object *s);

/*transformation.c*/

void			rotate_object(t_object *object, t_vector new_orientation);
void			rotate_vector(t_vector *v, t_vector k, float theta);
void			translate_object(t_object *object, t_vector delta);

/*utils.c*/

void			select_object(t_object *object, t_data *data);
int				min(int a, int b);
int				max(int a, int b);
char			*trim_newline(char *str);
void			light_helper(t_vector *f_col, t_data *data, t_ray *ray);

/*validation.c*/

int				validate(char *line);

/*validation_utils.c*/

int				is_double(char *ptr);
int				is_color(char *ptr);
int				is_vector(char *ptr);
int				is_int(char *ptr);

/*vector.c*/

t_vector		reflect_vector(t_vector light_dir, t_vector normal);
t_vector		vector(double x, double y, double z);
t_vector		cross_product(t_vector v1, t_vector v2);
double			dot(t_vector v1, t_vector v2);
int				is_normalized_vector(t_vector v);

/*vector_geometry.c*/

double			v_len(t_vector v);
double			v_dist(t_vector a, t_vector b);
t_vector		normalize_vector(t_vector v);

/*vector_math.c*/

t_vector		v_mul(double t, t_vector v);
t_vector		v_sub(t_vector v1, t_vector v2);
t_vector		v_sum(t_vector v1, t_vector v2);

#endif
