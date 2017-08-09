#include "all.h"

int GetMapCellPicId(int tileId, int x, int y)
{
	errorCase(tileId < 0 || TILE_MAX <= tileId);
	errorCase(x < 0 || TILE_W <= x);
	errorCase(y < 0 || TILE_H <= y);

	return D_TILE_00 + tileId * TILE_W * TILE_H + y * TILE_W + x | DTP;
}
int GetMiniMapCellPicId(int tileId, int x, int y)
{
	errorCase(tileId < 0 || TILE_MAX <= tileId);
	errorCase(x < 0 || MINITILE_W <= x);
	errorCase(y < 0 || MINITILE_H <= y);

	return D_MINITILE_00 + tileId * MINITILE_W * MINITILE_H + y * MINITILE_W + x | DTP;
}
int GetIconPicId(int x, int y)
{
	errorCase(x < 0 || 16 <= x);
	errorCase(y < 0 || 22 <= y);

	return D_ICONSET_00 + y * 16 + x | DTP;
}

void GetAround(Around_t *around, int x, int y, int size)
{
	errorCase(!around);
	errorCase(!m_isRange(x, 0, GDc.Field_W - 1));
	errorCase(!m_isRange(y, 0, GDc.Field_H - 1));
	errorCase(!m_isRange(size, AROUND_SIZE_MIN, AROUND_SIZE_MAX));

	int ard_sz = size * MAPCELL_W;

	int map_x = (x + 16 - ard_sz / 2) / MAPCELL_W;
	int map_y = (y + 16 - ard_sz / 2) / MAPCELL_H;

	int fld_x = x - (map_x * MAPCELL_W + ard_sz / 2);
	int fld_y = y - (map_y * MAPCELL_H + ard_sz / 2);

	errorCase(!m_isRange(fld_x, -16, 15)); // 2bs
	errorCase(!m_isRange(fld_y, -16, 15)); // 2bs

	zeroclear(around);

	for(int xc = 0; xc < size; xc++)
	for(int yc = 0; yc < size; yc++)
	{
		around->Map[xc][yc] = GDc.Map->RefCell(map_x + xc, map_y + yc, GDc.CommonMapCell);
	}
	around->Pos = makeI2D(fld_x, fld_y);
	around->MapPos = makeI2D(map_x, map_y);
}
int GetDir(double x, double y) // ret: 11 Å` 33
{
	int xDir;
	int yDir;

	     if(x < -MICRO) xDir = 1;
	else if(MICRO < x)  xDir = 3;
	else                xDir = 2;

	     if(y < -MICRO) yDir = 1;
	else if(MICRO < y)  yDir = 3;
	else                yDir = 2;

	return xDir * 10 + yDir;
}

int IsOutOfField(double x, double y, double margin)
{
	return
		x < -margin || GDc.Field_W + margin < x ||
		y < -margin || GDc.Field_H + margin < y;
}
int IsOutOfField_PS(PlayerShot_t *i, double margin)
{
	return IsOutOfField(i->X, i->Y, margin);
}
