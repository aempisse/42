#include "fractol.h"

t_color			ft_color0(int loop, int max_loop)
{
	t_color		color;

	if (loop == max_loop)
		color.u = 0x00000000;
	else
	{
		color.b.a = 0x00;
		color.b.r = ((double)loop / (double)max_loop) * 255;
		color.b.g = 0x00;
		color.b.b = 0x00;
	}
	return (color);
}

t_color			ft_color1(int loop, int max_loop)
{
	t_color		color;
	double		ratio;

	color.u = 0x00000000;
	if (loop != max_loop)
	{
		ratio = ((double)loop / (double)max_loop);
		if ((double)loop < (double)max_loop / 2)
		{
			color.u = ((double)loop < (double)max_loop / 4) ? 
			 (0.25 - ratio) * 4 * 0x00FFFFFF + ratio * 4 * 0x0000008B :
			 (0.5 - ratio) * 4 * 0x0000008B + (ratio - 0.25) * 4 * 0x00FFFFFF;
		}
		else
		{
			color.u = ((double)loop < 3 * (double)max_loop / 4) ? 
			 (0.75 - ratio) * 4 * 0x00FFFFFF + (ratio - 0.5) * 4 * 0x00FFC125 :
			 ((1 - ratio) * 4 * 0x00FFC125) + (ratio - 0.75) * 4 * 0x00FFFFFF;
		}
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
	double		ratio;

	color.u = 0x00000000;
	if (loop != max_loop)
	{
		ratio = ((double)loop / (double)max_loop);
		if ((double)loop < (double)max_loop / 2)
		{
			color.b.r = ((double)loop < (double)max_loop / 4) ? 
			 (0.25 - ratio) * 4 * 0xFF + ratio * 4 * 0x00 :
			 (0.5 - ratio) * 4 * 0x00 + (ratio - 0.25) * 4 * 0xFF;
			color.b.g = ((double)loop < (double)max_loop / 4) ? 
			 (0.25 - ratio) * 4 * 0xFF + ratio * 4 * 0x00 :
			 (0.5 - ratio) * 4 * 0x00 + (ratio - 0.25) * 4 * 0xFF;
			color.b.b = ((double)loop < (double)max_loop / 4) ? 
			 (0.25 - ratio) * 4 * 0xFF + ratio * 4 * 0x8B :
			 (0.5 - ratio) * 4 * 0x8B + (ratio - 0.25) * 4 * 0xFF;
		}
		else
		{
			color.b.r = ((double)loop < 3 * (double)max_loop / 4) ? 
			 (0.75 - ratio) * 4 * 0xFF + (ratio - 0.5) * 4 * 0xFF :
			 ((1 - ratio) * 4 * 0xFF) + (ratio - 0.75) * 4 * 0xFF;
			color.b.g = ((double)loop < 3 * (double)max_loop / 4) ? 
			 (0.75 - ratio) * 4 * 0xFF + (ratio - 0.5) * 4 * 0xC1 :
			 ((1 - ratio) * 4 * 0xC1) + (ratio - 0.75) * 4 * 0xFF;
			color.b.b = ((double)loop < 3 * (double)max_loop / 4) ? 
			 (0.75 - ratio) * 4 * 0xFF + (ratio - 0.5) * 4 * 0x25 :
			 ((1 - ratio) * 4 * 0x25) + (ratio - 0.75) * 4 * 0xFF;
		}
	}
	return (color);
}

void			ft_switch_color(t_env *env)
{
	env->color_id = (env->color_id + 1) % 5;
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
}
