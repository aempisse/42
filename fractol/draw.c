#include "fractol.h"

void			ft_put_image(t_image *img, int pos, t_color color)
{
	int			to;

	to = pos + img->opp;
	while (pos < to)
	{
		img->data[pos] = color.b.b;
		color.u >>= 8;
		pos++;
	}
}

t_color			ft_mandelbrot_color(int loop)
{
	t_color		color;

	if (loop == LOOP)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = 0x00;
		color.b.g = loop * 255 / LOOP;
		color.b.b = 0x00;
	}
	return (color);
}

int			ft_mandelbrot_loop(t_env *env, long int x, long int y)
{
	const t_complex c = (t_complex){x / env->zoom, y / env->zoom};
	t_complex		z;
	t_complex		sq;
	int				i;

	z = (t_complex){0, 0};
	sq = (t_complex){0, 0};
	i = LOOP;
	while (((sq.r + sq.i) < 4) && i-- > 0)
	{
		sq.r = z.r * z.r;
		sq.i = z.i * z.i;
		z.r = sq.r - sq.i + c.r;
		z.i = 2 * z.r * z.i + c.i;
	}
	return (LOOP - i);
}

void			mandelbrot(t_env *env)
{
	t_lpt		pt;
	t_lpt		max;

	max = (t_lpt){WIDTH + env->offset.x, HEIGHT + env->offset.y};
	pt.y = env->offset.y;
	while (pt.y++ < max.y)
	{
		pt.x = env->offset.x;
		while (pt.x++ < max.x)
		{
			ft_put_image(env->img, (env->img->width * (pt.y - env->offset.y) + (pt.x - env->offset.x)) * 
				env->img->opp, ft_mandelbrot_color(ft_mandelbrot_loop(env, pt.x, pt.y)));
		}
	}
	env->rerender = 1;
}
