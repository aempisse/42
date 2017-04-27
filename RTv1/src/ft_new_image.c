#include "../rtv1.h"

t_image	*ft_new_image(void *mlx, int width, int height, int thread)
{
	t_image		*img;

	if ((img = (t_image*)malloc(sizeof(t_image))) == NULL)
		ft_error("Error: malloc failed.\n");
	img->img = mlx_new_image(mlx, width, (height / thread));
	img->data = (unsigned char*)mlx_get_data_addr(img->img, &img->opp,
		&img->l_size, &img->endian);
	img->opp = img->opp / 8;
	img->width = width;
	img->height = height / thread;
	return (img);
}