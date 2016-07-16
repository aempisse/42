#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIDTH 1280
# define HEIGHT 700

typedef struct	s_image
{
	unsigned char	*data;
	void			*img;
	int				width;
	int				height;
	int				l_size;
	int				opp;
	int				endian;
}				t_image;

typedef struct	s_argb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}				t_argb;

typedef union	u_color
{
	t_argb			b;
	unsigned int	u;
	int				i;
}				t_color;

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_pt			offset;
	t_image			*img;
	double			pt_dist;
	double			max_z;
	double			min_z;
}				t_env;

#endif