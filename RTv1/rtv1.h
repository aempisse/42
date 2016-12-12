#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
//# include <mlx.h>
# include "minilibx/mlx.h"

# define WIDTH 640
# define HEIGHT 360

typedef struct	s_control
{
	int			menu;
	int			nbr_max;
	int			nbr_sp;
	int			ctm_1;
	int			i;
	int			mod;
	int			neg;
	int			stop_add;
	double		num;
	char		*name_obj;
}				t_control;

typedef struct	s_double3
{
	double		x;
	double		y;
	double		z;
}				t_double3;

typedef struct	s_plane
{
	t_double3	pos;
}				t_plane;

typedef struct	s_sphere
{
	t_double3	pos;
	double		radius;
	// t_color		color;
}				t_sphere;

typedef struct	s_env
{
	void		*mlx;
	void		*win_scene;
	void		*win_control;
	t_image		*img;
	t_array		*sphere;
	t_array		*plane;
	t_control	*control;
	int			render;
	int			render_scn;
}				t_env;

void			ft_load_file(int fd, t_env *env);
void			draw_control(t_env *env);
int				loop_hook(t_env *env);
int				key_hook(int keycode, t_env *env);
void			ft_draw_small_arrow(t_env *env);
void			draw_square(t_env *env);
void			ft_draw_left_arrow(t_env *env);
void			ft_draw_right_arrow(t_env *env);
void			draw_value(t_env *env);
int				key_obj_menu(int keycode, t_env *env);
int				key_obj_in(int keycode, t_env *env);


#endif