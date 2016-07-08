#include "fdf.h"
#include <stdlib.h>

double			ft_posd(int min, int max, int curr)
{
	if (curr <= min || curr >= max)
		return ((curr <= min) ? 0 : 1);
	if (min < 0)
		return ((double)(curr - min) / (double)(max - min));
	return ((double)(curr + min) / (double)(max + min));
}

int				ft_mixd(int a, int b, double pos)
{
	if (a > b)
		return (a - DOWN((double)(a - b) * pos));
	return (DOWN((double)(b - a) * pos) + a);
}

t_color			ft_gradientget(t_array *gradient, double pos)
{
	t_color			*tmp1;
	t_color			*tmp2;
	t_color			c;
	int				down;

	if (pos >= 1 || gradient->length == 1)
		return (*((t_color*)gradient->data[gradient->length - 1]));
	if (pos <= 0)
		return (*((t_color*)gradient->data[0]));
	pos *= gradient->length - 1;
	down = DOWN(pos);
	tmp1 = gradient->data[down];
	tmp2 = gradient->data[down + 1];
	pos -= down;
	c.b.a = ft_mixd(tmp1->b.a, tmp2->b.a, pos);
	c.b.r = ft_mixd(tmp1->b.r, tmp2->b.r, pos);
	c.b.g = ft_mixd(tmp1->b.g, tmp2->b.g, pos);
	c.b.b = ft_mixd(tmp1->b.b, tmp2->b.b, pos);
	return (c);
}

t_array			*ft_gradientnew(char *input)
{
	int				i;
	t_array			*gradient;
	t_color			*tmp;
	char			**colors;

	colors = ft_strsplit(input, ';');
	gradient = ft_arraynew();
	i = -1;
	while (colors[++i] != NULL)
	{
		tmp = (t_color*)malloc(sizeof(t_color));
		*tmp = ft_atocolor(colors[i]);
		ft_arrayadd(gradient, tmp);
		free(colors[i]);
	}
	if (i < 0)
		ft_error("Error: Bad gradient.\n");
//		ft_arrayadd(gradient, ft_memdup(tmp, sizeof(t_color)));
//	else
//		ft_error("Error: Bad gradient.\n");
	free(colors);
	return (gradient);
}

t_color			ft_atocolor(char *str)
{
	t_color			color;
	t_buff			buff;

	buff = (t_buff){str, 0, ft_strlen(str)};
	ft_parsenot(&buff, "0123456789");
	color.b.r = (unsigned char)ft_parseint(&buff);
	ft_parsenot(&buff, "0123456789");
	color.b.g = (unsigned char)ft_parseint(&buff);
	ft_parsenot(&buff, "0123456789");
	color.b.b = (unsigned char)ft_parseint(&buff);
	ft_parsenot(&buff, "0123456789");
	color.b.a = (buff.data[buff.i] != '\0') ? (unsigned char)ft_parseint(&buff) : 255;
	return (color);
}