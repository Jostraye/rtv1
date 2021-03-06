/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/11 16:27:36 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <pthread.h>
# define WINY 1000
# define WINZ 1000
# define FOV 1000
# define TH_NB 50
# define ALPHA_SPEC 100
# define SHADOW_BIAS 0.001

typedef struct		s_vc
{
	double			x;
	double			y;
	double			z;
}					t_vc;

typedef struct		s_obj
{
	int				type;
	t_vc			rot;
	t_vc			pos;
	t_vc			coef;
	int				col;
	double			size;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*image;
	int				*imgstr;
	int				bpp;
	int				thread_int;
	int				s_l;
	int				endian;
	int				y;
	int				z;
	int				nb_eye;
	double			smax;
	double			t;
	double			s;
	double			a;
	double			b;
	double			c;
	double			cost;
	t_vc			ray;
	t_vc			eye_lookfrom;
	t_vc			eye_rot;
	t_vc			n;
	t_vc			lm;
	t_vc			rm;
	t_vc			v;
	t_vc			v2;
	t_vc			offset;
	pthread_t		pth[TH_NB];
	t_obj			*obj_link;
	t_obj			*light_link;
}					t_env;

/*
** RAYTRACER
*/

int					create_image(t_env *e);
void				draw_point(t_env *e, int x, int y, unsigned int color);
void				*scene_plot(void *arg);
void				create_ray(t_env *e);
double				distance_to_inter(t_env *e, t_obj *obj_list,
					t_vc ray, t_vc p);
t_obj				*nearest_node(t_env *e);
void				compute_scene_vectors(t_env *e, t_obj *tmp);

/*
** MATHS
*/

double				car(double a);
t_vc				rot_x(t_vc vc, int t);
t_vc				rot_y(t_vc vc, int t);
t_vc				rot_z(t_vc vc, int t);
t_vc				rot_all_axis(t_vc vc, t_vc obj);
double				vec_squ_sum(t_vc v1);
t_vc				vec_add(t_vc v1, t_vc v2);
t_vc				vec_sub(t_vc v1, t_vc v2);
double				vec_x(t_vc v1, t_vc v2);
double				vec_mod(t_vc v);
t_vc				vec_norm(t_vc v);
t_vc				vec_mult(t_vc v, double x);
double				vec_dot(t_vc v1, t_vc v2);

/*
** SHAPES INTERSECTIONS
*/

double				inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				inter_plane(t_vc ray, t_vc offset, t_obj *obj);
double				inter_cyl(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				inter_sph(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				quadratic_solver(t_env *e);

/*
** KEYBOARD / MOUSE
*/

void				translation(int key, t_env *e);
void				rotation(int key, t_env *e);
int					deal_key(int key, t_env *e);

/*
** LIGHTING
*/

void				normal_vectors(t_env *e, t_obj *obj);
int					shadows(t_env *e, t_obj *tmp, t_obj *olst,
					t_obj *light_obj);

/*
** COLORS
*/

unsigned long		rgb_to_hexa(t_obj *obj, t_env *e);
int					multiply_color(int hex, double mult);
int					add_color(int hex1, int hex2);
int					specular_diffuse(int color, t_obj *light,
					t_obj *obj, t_env *e);

/*
** STRUCTURES INITIALIZATION
*/

t_env				*init_env(void);
int					init_mlx(t_env *e);
t_vc				init_vc(double x, double y, double z);

/*
** OBJECTS
*/

void				obj_add(t_obj **beg, t_obj *n);
void				clear_list(t_obj *head);

/*
** ERROR MGT
*/

void				ft_usage(void);
void				ft_malloc_error(t_env *e);
void				exit_message(char *str);

/*
** FREE STRUCTURES
*/

void				free_split(char **split);

/*
** PARSER
*/

int					ft_htod(char c);
int					ft_htoi(char *str);
double				ft_atof(char *c);
int					ft_iscolor(char *str);
int					ft_isnumber(char *str);
int					check_value(char **str);
int					name_type(char *str);
void				error_messages(int error);
t_obj				*attribute_object(char **tab_values);
char				*tabtospace(char *str);
int					attribute_scene(char *str, t_env *e);
int					parser(char **av, t_env *e);
int					create_objects(t_env *e, char **tab_values);

#endif
