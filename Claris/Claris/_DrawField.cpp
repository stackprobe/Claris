#include "all.h"

// ---- DMC_* ----

static void DMC_PicId(int dr_x, int dr_y, int picId)
{
	DrawSimple(picId, dr_x, dr_y);
}
/*
	animeFrm: 0 == アニメ無効, 0< == 1コマのフレーム数
*/
static void DMC_Water(int dr_x, int dr_y, int map_x, int map_y, int tileId, int tile_x, int tile_y, int animeFrm, int (*funcIsWater)(MapCell_t *))
{
	int aw[3][3];

	GetAround(aw, map_x, map_y, funcIsWater);

	i2D_t tPos[2][2];

	     if(aw[0][1] && aw[1][0]) tPos[0][0] = aw[0][0] ? makeI2D(2, 4) : makeI2D(2, 0);
	else if(aw[0][1])             tPos[0][0] =            makeI2D(2, 2);
	else if(aw[1][0])             tPos[0][0] =            makeI2D(0, 4);
	else                          tPos[0][0] =            makeI2D(0, 2);

	     if(aw[2][1] && aw[1][0]) tPos[1][0] = aw[2][0] ? makeI2D(1, 4) : makeI2D(3, 0);
	else if(aw[2][1])             tPos[1][0] =            makeI2D(1, 2);
	else if(aw[1][0])             tPos[1][0] =            makeI2D(3, 4);
	else                          tPos[1][0] =            makeI2D(3, 2);

	     if(aw[0][1] && aw[1][2]) tPos[0][1] = aw[0][2] ? makeI2D(2, 3) : makeI2D(2, 1);
	else if(aw[0][1])             tPos[0][1] =            makeI2D(2, 5);
	else if(aw[1][2])             tPos[0][1] =            makeI2D(0, 3);
	else                          tPos[0][1] =            makeI2D(0, 5);

	     if(aw[2][1] && aw[1][2]) tPos[1][1] = aw[2][2] ? makeI2D(1, 3) : makeI2D(3, 1);
	else if(aw[2][1])             tPos[1][1] =            makeI2D(1, 5);
	else if(aw[1][2])             tPos[1][1] =            makeI2D(3, 3);
	else                          tPos[1][1] =            makeI2D(3, 5);

	int div;
	int mod;

	if(animeFrm)
	{
		div = ActFrame / animeFrm;
		mod = ActFrame % animeFrm;
	}
	else
	{
		div = 0;
		mod = 0;
	}

	for(int anime = 0; anime < (mod ? 2 : 1); anime++)
	{
		int aPos = (div + anime) % 3;

		if(anime)
			DPE_SetAlpha((double)mod / animeFrm);

		for(int x = 0; x < 2; x++)
		for(int y = 0; y < 2; y++)
		{
			DrawSimple(
				GetMiniMapCellPicId(
					tileId,
					tile_x + tPos[x][y].X + aPos * 4,
					tile_y + tPos[x][y].Y
					),
				dr_x + x * MINIMAPCELL_W,
				dr_y + y * MINIMAPCELL_H
				);
		}
	}
	DPE_SetAlpha(1.0);
}

// ---- for DMC_Water ----

static int DMCW_IsWater(MapCell_t *mc)
{
	return mc->JimenId == J_WATER_IN_GREEN || mc->JimenId == J_ERROR;
}
static int DMCW_IsGrassInGreen(MapCell_t *mc)
{
	return mc->JimenId == J_GRASS_IN_GREEN || mc->JimenId == J_ERROR;
}
static int DMCW_IsFlowerInGreen(MapCell_t *mc)
{
	return mc->JimenId == J_FLOWER_IN_GREEN || mc->JimenId == J_ERROR;
}

// ----

static void DrawMapCell(int dr_x, int dr_y, int map_x, int map_y)
{
	MapCell_t *mc = GDc.Map->RefCell(map_x, map_y, NULL);

	if(!mc)
		return;

	DPE.TL = GDc.DJ;

	switch(mc->JimenId)
	{
	case J_ERROR: DMC_PicId(dr_x, dr_y, P_DUMMY); break;
	case J_GREEN: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_A2, 0, 0)); break;
	case J_WATER_IN_GREEN: DMC_Water(dr_x, dr_y, map_x, map_y, TILE_A1, 16, 0, 30, DMCW_IsWater); break;
	case J_GRASS_IN_GREEN: DMC_Water(dr_x, dr_y, map_x, map_y, TILE_A2, 4, 6, 0, DMCW_IsGrassInGreen); break;
	case J_FLOWER_IN_GREEN: DMC_Water(dr_x, dr_y, map_x, map_y, TILE_A2, 0, 6, 0, DMCW_IsFlowerInGreen); break;

	default:
		error();
	}

	DPE_Reset();
	DPE.TL = GDc.DK;

	switch(mc->KouzouId)
	{
	case K_NONE: break;
	case K_WOOD: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 4, 6)); break;
	case K_WOOD_1: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 6, 5)); break;
	case K_WOOD_3: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 7, 5)); break;
	case K_WOOD_7: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 6, 4)); break;
	case K_WOOD_9: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 7, 4)); break;
	case K_WOOD_19: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 6, 6)); break;
	case K_WOOD_37: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_B, 7, 6)); break;
	case K_BROKEN_STELE_T: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_E, 12, 9)); break;
	case K_BROKEN_STELE_B: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_E, 12, 10)); break;
	case K_BROKEN_STELE: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_E, 11, 10)); break;
	case K_BROKEN_STELE_MOSS: DMC_PicId(dr_x, dr_y, GetMapCellPicId(TILE_E, 11, 9)); break;

	default:
		error();
	}

	DPE_Reset();
}
void DrawField(void)
{
	int cam_x = GDc.ICameraX;
	int cam_y = GDc.ICameraY;

	errorCase(cam_x < 0);
	errorCase(cam_y < 0);

	int dr_l = -cam_x % MAPCELL_W;
	int dr_t = -cam_y % MAPCELL_H;

	int map_l = cam_x / MAPCELL_W;
	int map_t = cam_y / MAPCELL_H;

	/*
		800 / 32 == 25
		600 / 32 == 18.75 -> 19
	*/
	int map_w = 25;
	int map_h = 19;

	if(dr_l)
		map_w++;

	if(dr_t)
		map_h++;

	for(int x = 0; x < map_w; x++)
	for(int y = 0; y < map_h; y++)
	{
		DrawMapCell(
			dr_l + x * MAPCELL_W,
			dr_t + y * MAPCELL_H,
			map_l + x,
			map_t + y
			);
	}
}
