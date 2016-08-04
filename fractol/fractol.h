#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIDTH 675
# define HEIGHT 600
# define LOOP 50

typedef	struct s_lpt
{
	long int		x;
	long int		y;
}				t_lpt;

typedef struct	s_complex
{
	long double		r;
	long double		i;
}				t_complex;

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_image			*img;
	t_lpt			offset;
	long double		zoom;
	long double		zoom_offset;
	int				rerender;
	t_color			(*color)(int, int);
	int				color_id;
	int				loop;
}				t_env;

void			mandelbrot(t_env *env);
int				ft_mandelbrot_loop(t_env *env, long int x, long int y);
void			ft_put_image(t_image *img, int pos, t_color color);

void			ft_switch_color(t_env *env);
t_color			ft_color1(int loop, int max_loop);
t_color			ft_color0(int loop, int max_loop);

int				expose_hook(t_env *env);
int				key_hook(int keycode, t_env *env);
int				mouse_hook(int button, int x, int y, t_env *env);
int				loop_hook(t_env *env);

#endif