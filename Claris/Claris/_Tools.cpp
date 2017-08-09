#include "all.h"

int IsOutOfScreen_IC(double x, double y, double margin) // ignore camera
{
	return
		x < -margin || SCREEN_W + margin <= x ||
		y < -margin || SCREEN_H + margin <= y;
}
int IsOutOfScreen(double x, double y, double margin)
{
	return IsOutOfScreen_IC(x - GDc.CameraX, y - GDc.CameraY, margin);
}
