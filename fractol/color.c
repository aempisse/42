#include "fractol.h"

t_color			ft_color0(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = (loop % 25) * 10;
		color.b.g = (loop % 20) * 10;
		color.b.b = (loop % 15) * 10;
	}
	return (color);
}

t_color			ft_color1(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = loop % 200;
		color.b.g = loop % 150;
		color.b.b = loop % 50;
	}
	return (color);
}

t_color			ft_color2(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = (loop % 15) * 10;
		color.b.g = (loop % 80) * 2;
		color.b.b = (loop % 51) * 5;
	}
	return (color);
}

t_color			ft_color3(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = 255 - (loop % 255);
		color.b.g = (loop % 10) * 10;
		color.b.b = (loop % 125) * 2;
	}
	return (color);
}

t_color			ft_color4(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = loop % 256;
		color.b.g = 0x00;
		color.b.b = 255 - (loop % 256);
	}
	return (color);
}


t_color			ft_color5(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = loop % 256;
		color.b.g = loop % 256;
		color.b.b = loop % 256;
	}
	return (color);
}

void			ft_switch_color(t_env *env)
{
	env->color_id = (env->color_id + 1) % 6;
	if (env->color_id == 0)
		env->color = &ft_color0;
	if (env->color_id == 1)
		env->color = &ft_color1;
	if (env->color_id == 2)
		env->color = &ft_color2;
	if (env->color_id == 3)
		env->color = &ft_color3;
	if (env->color_id == 4)
		env->color = &ft_color4;
	if (env->color_id == 5)
		env->color = &ft_color5;
}
