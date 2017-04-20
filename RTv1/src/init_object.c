#include "../rtv1.h"

void			init_light_obj(t_env *env, t_pars *pars, int obj,
	t_light **light)
{
	t_light		*new_obj;

	new_obj = light_new(obj);
	light_add(light, new_obj);
}

void			init_object(t_env *env, t_pars *pars, int obj,
	t_object **object)
{
	t_object	*new_obj;
	t_object	*tmp;

	new_obj = object_new(obj);
	object_add(object, new_obj);
}
