#include "fdf.h"

double			ft_position_z(int min, int max, int curr)
{
	if (curr <= min || curr >= max)
		return ((curr <= min) ? 0 : 1);
	if (min < 0)
		return ((double)(curr - min) / (double)(max - min));
	return ((double)(curr + min) / (double)(max + min));
}

int				ft_mix_color(int a, int b, double pos)
{
	if (a > b)
		return (a - DOWN((double)(a - b) * pos));
	return (DOWN((double)(b - a) * pos) + a);
}

t_color			ft_get_color(t_array *color, double pos)
{
	t_color			*tmp1;
	t_color			*tmp2;
	t_color			c;
	int				down;

	if (pos >= 1 || color->length == 1)
		return (*((t_color*)color->data[color->length - 1]));
	if (pos <= 0)
		return (*((t_color*)color->data[0]));
	pos *= color->length - 1;
	down = DOWN(pos);
	tmp1 = color->data[down];
	tmp2 = color->data[down + 1];
	pos -= down;
	c.b.a = ft_mix_color(tmp1->b.a, tmp2->b.a, pos);
	c.b.r = ft_mix_color(tmp1->b.r, tmp2->b.r, pos);
	c.b.g = ft_mix_color(tmp1->b.g, tmp2->b.g, pos);
	c.b.b = ft_mix_color(tmp1->b.b, tmp2->b.b, pos);
	return (c);
}

t_array			*ft_new_color(char *input)
{
	int				i;
	t_array			*color;
	t_color			*tmp;
	char			**color_split;

	color_split = ft_strsplit(input, ';');
	color = ft_array_new();
	i = -1;
	while (color_split[++i] != NULL)
	{
		tmp = (t_color*)malloc(sizeof(t_color));
		*tmp = ft_atocolor(color_split[i]);
		ft_array_add(color, tmp);
		free(color_split[i]);
	}
	if (i == 0)
		ft_error("Error: Bad gradient.\n");
	free(color_split);
	return (color);
}

t_color			ft_atocolor(char *str)
{
	t_color			color;
	t_buff			buff;

	buff = (t_buff){str, 0, ft_strlen(str)};
	ft_parse_not(&buff, "0123456789");
	color.b.r = (unsigned char)ft_parse_int(&buff);
	ft_parse_not(&buff, "0123456789");
	color.b.g = (unsigned char)ft_parse_int(&buff);
	ft_parse_not(&buff, "0123456789");
	color.b.b = (unsigned char)ft_parse_int(&buff);
	ft_parse_not(&buff, "0123456789");
	color.b.a = (buff.data[buff.i] != '\0') ? 
	(unsigned char)ft_parse_int(&buff) : 255;
	return (color);
}