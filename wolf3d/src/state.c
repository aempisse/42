#include "../wolf3d.h"

static void			state_1(t_env *env)
{
	env->state = 1;
	env->map[8][4] = 1;
	env->map[8][8] = 5;
}

static void			state_2(t_env *env)
{
	env->state = 2;
	env->map[8][8] = 0;
	env->color = &color1;
}

void			change_state(t_env *env)
{
	if (env->state == 0 && (int)env->pos.x == 8 && (int)env->pos.y == 5)
		state_1(env);
	else if (env->state == 1 && (int)env->pos.x == 8 && (int)env->pos.y == 7)
		state_2(env);
}