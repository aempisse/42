#include "../rtv1.h"

static t_double3	hex_to_double(char *str)
{
	char		*tmp;
	t_double3	rgb;
	double		hex[6];
	int			i;

	tmp = ft_strnew(ft_strlen(str));
	tmp = ft_strcpy(tmp, str);
	i = 0;
	while (tmp[i] != '\0' && i < 7)
	{
		tmp[i] = ft_toupper(tmp[i]);
		if (tmp[i] >= 48 && tmp[i] <= 57)
			hex[i] = tmp[i] - 48;
		else if (tmp[i] >= 65 && tmp[i] <= 70)
			hex[i] = tmp[i] - 55;
		else
			ft_error("Mauvais typage hexadecimal.");
		i++;
	}
	rgb.x = (hex[0] * 16 + hex[1]) / 255;
	rgb.y = (hex[2] * 16 + hex[3]) / 255;
	rgb.z = (hex[4] * 16 + hex[5]) / 255;
	return (rgb);
}

void				check_color_light(t_light **light, char *value)
{
	t_light		*tmp;
	char		*tmp_c;

	tmp_c = ft_strnew(7);
	tmp_c = ft_strcpy(tmp_c, value);
	tmp = *light;
	if (ft_strcmp(tmp_c, "red") == 0)
		tmp->color = hex_to_double(RED);
	else if (ft_strcmp(tmp_c, "blue") == 0)
		tmp->color = hex_to_double(BLUE);
	else if (ft_strcmp(tmp_c, "green") == 0)
		tmp->color = hex_to_double(GREEN);
	else if (ft_strcmp(tmp_c, "lightblue") == 0)
		tmp->color = hex_to_double(LIGHT_BLUE);
	else if (ft_strcmp(tmp_c, "lightgreen") == 0)
		tmp->color = hex_to_double(LIGHT_GREEN);
	else if (ft_strcmp(tmp_c, "orange") == 0)
		tmp->color = hex_to_double(ORANGE);
	else if (ft_strcmp(tmp_c, "pink") == 0)
		tmp->color = hex_to_double(PINK);
	else if (ft_strcmp(tmp_c, "purple") == 0)
		tmp->color = hex_to_double(PURPLE);
	else
		tmp->color = hex_to_double(tmp_c);
}

void				check_color_obj(t_object **object, char *value)
{
	t_object	*tmp;
	char		*tmp_c;

	tmp_c = ft_strnew(7);
	tmp_c = ft_strcpy(tmp_c, value);
	tmp = *object;
	if (ft_strcmp(tmp_c, "red") == 0)
		tmp->color = hex_to_double(RED);
	else if (ft_strcmp(tmp_c, "blue") == 0)
		tmp->color = hex_to_double(BLUE);
	else if (ft_strcmp(tmp_c, "green") == 0)
		tmp->color = hex_to_double(GREEN);
	else if (ft_strcmp(tmp_c, "lightblue") == 0)
		tmp->color = hex_to_double(LIGHT_BLUE);
	else if (ft_strcmp(tmp_c, "lightgreen") == 0)
		tmp->color = hex_to_double(LIGHT_GREEN);
	else if (ft_strcmp(tmp_c, "orange") == 0)
		tmp->color = hex_to_double(ORANGE);
	else if (ft_strcmp(tmp_c, "pink") == 0)
		tmp->color = hex_to_double(PINK);
	else if (ft_strcmp(tmp_c, "purple") == 0)
		tmp->color = hex_to_double(PURPLE);
	else
		tmp->color = hex_to_double(tmp_c);
}
