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

	new_obj = object_new(obj);
	object_add(object, new_obj);
}

void			init_neg_obj(t_env *env, t_pars *pars, t_negobj **neg_obj)
{
	t_negobj	*new_obj;

	new_obj = neg_obj_new();
	neg_obj_add(neg_obj, new_obj);
}
