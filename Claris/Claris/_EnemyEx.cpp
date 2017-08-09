/*
	‘å‚«‚­‚È‚è‚»‚¤‚È EnemyEachFrame, LoadEnemy ‚ð‚±‚±‚É’u‚­B
*/

#include "all.h"

int EnemyEachFrame(Enemy_t *e) // ret: dead
{
	switch(e->EnemyId)
	{
	case E_START: return EEF_Start(e);
	case E_ITEM_00: return EEF_Item(e);

	default:
		error();
	}
}
Enemy_t *LoadEnemy(MapCell_t *mc, int map_x, int map_y)
{
	double x = map_x * MAPCELL_W + MAPCELL_W / 2;
	double y = map_y * MAPCELL_H + MAPCELL_H / 2;

	if(m_isRange(mc->EnemyId, E_ITEM_00, E_ITEM_00_END))
	{
		return CreateEnemy(mc, E_ITEM_00, x, y, mc->EnemyId - E_ITEM_00);
	}
	switch(mc->EnemyId)
	{
	case E_START: return CreateEnemy(mc, mc->EnemyId, x, y);

	default:
		error();
	}
	error(); // 2bs
	return NULL; // dummy
}
