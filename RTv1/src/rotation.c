#include "../rtv1.h"

static t_double3	rotation_x(t_double3 point, double angle)
{
	t_double3	new_point;

	if (abs_double(angle) < 0.00001)
		return (point);
	angle = angle * (PI / 180.0);
	new_point.x = point.x;
	new_point.y = point.y * cos(angle) - point.z * sin(angle);
	new_point.z = point.y * sin(angle) + point.z * cos(angle);
	return (new_point);
}

static t_double3	rotation_y(t_double3 point, double angle)
{
	t_double3	new_point;

	if (abs_double(angle) < 0.00001)
		return (point);
	angle = angle * (PI / 180.0);
	new_point.x = point.x * cos(angle) + point.z * sin(angle);
	new_point.y = point.y;
	new_point.z = -point.x * sin(angle) + point.z * cos(angle);
	return (new_point);
}

static t_double3	rotation_z(t_double3 point, double angle)
{
	t_double3	new_point;

	if (abs_double(angle) < 0.00001)
		return (point);
	angle = angle * (PI / 180.0);
	new_point.x = point.x * cos(angle) - point.y * sin(angle);
	new_point.y = point.x * sin(angle) + point.y * cos(angle);
	new_point.z = point.z;
	return (new_point);
}

t_double3			rotation(t_double3 point, t_double3 angles)
{
	point = rotation_x(point, angles.x);
	point = rotation_y(point, angles.y);
	point = rotation_z(point, angles.z);
	return (point);
}
