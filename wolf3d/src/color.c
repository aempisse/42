#include "../wolf3d.h"

void			switch_color(t_env *env)
{
	env->color_id = (env->color_id + 1) % 2;
	if (env->color_id == 0)
		env->color = &color0;
	if (env->color_id == 1)
		env->color = &color1;
	// if (env->color_id == 2)
	// 	env->color = &color2;
}

t_color			color0(t_env *env, int y, int draw_start, int draw_end)
{
	t_color		color;


	if (y < draw_start)
		color.u = 0x00000000;
	else if (y < draw_end)
	{
		// if (TG(int, AG(t_tab*, env->map, env->map_pos.y), env->map_pos.x) == 5)
		if (env->map[env->map_pos.y][env->map_pos.x] == 5)
			color.u = 0x00FFFFFF;
		else
			color.u = 0x00000000;
	}
	else
		color.u = 0x00000000;
    return (color);
}

t_color			color1(t_env *env, int y, int draw_start, int draw_end)
{
	t_color		color;

	if (y < draw_start)
		color.u = 0x007EC0EE;
	else if (y < draw_end)
	{
		if (env->side == WEST)
			color.u = 0x00FF0000;
		if (env->side == EAST)
			color.u = 0x00FFFF00;
		if (env->side == SOUTH)
			color.u = 0x0000FF00;
		if (env->side == NORTH)
			color.u = 0x000000FF;
		// if (TG(int, AG(t_tab*, env->map, env->map_pos.y), env->map_pos.x) == 5)
		if (env->map[env->map_pos.y][env->map_pos.x] == 5)
			color.u = 0x00FFFFFF;
	}
	else
		color.u = 0x00F2F2F2;
    return (color);
}

// t_color			color2(t_env *env)
// {
// 	t_color		color;

// 	if (env->side == WEST)
//     	color.u = 0x00FF0000;
//     if (env->side == EAST)
//     	color.u = 0x00FFFF00;
//     if (env->side == SOUTH)
//     	color.u = 0x0000FF00;
//     if (env->side == NORTH)
//     	color.u = 0x000000FF;
//     if (TG(int, AG(t_tab*, env->map, env->map_pos.y), env->map_pos.x) == 5)
//     	color.u = 0x00FFD700;
//     return (color);
// }