#include "../rtv1.h"

t_light			*light_new(void)
{
	t_light		*light;

	if ((light = (t_light*)malloc(sizeof(t_light))) == NULL)
		ft_error("Error : malloc() failed.\n");
	light->position = (t_double3){0, 0, 0};
	light->direction = (t_double3){0, 0, 0};
	light->color = (t_double3){0, 0, 0};
	return (light);
}

void			light_add(t_light **first, t_light *new)
{
	new->next = *first;
	*first = new;
}

t_object		*object_new(void)
{
	t_object	*object;

	if ((object = (t_object*)malloc(sizeof(t_object))) == NULL)
		ft_error("Error : malloc() failed.\n");
	object->type = 0;
	object->position = (t_double3){0, 0, 0};
	object->rotation = (t_double3){0, 0, 0};
	object->radius = 0;
	object->color = (t_double3){0, 0, 0};
	object->reflexion = 0;
	object->transparency = 0;
	object->gloss = 0;
	object->refraction = 0;
	object->*next = NULL;
	return (object);
}

void			object_add(t_object **first, t_object *new)
{
	new->next = *first;
	*first = new;
}
