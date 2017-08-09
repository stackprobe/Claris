#include "all.h"

static MapCell_t *MCL_Forest(int color)
{
	switch(color)
	{
	case PAINTPAL_01_1: return CreateMapCell(J_GREEN, K_NONE, E_START);
	case PAINTPAL_01_2: return CreateMapCell(J_GREEN, K_BROKEN_STELE, E_NONE, 1, 1);
	case PAINTPAL_02_1: return CreateMapCell(J_GREEN, K_BROKEN_STELE_T, E_NONE);
	case PAINTPAL_02_2: return CreateMapCell(J_GREEN, K_BROKEN_STELE_B, E_NONE, 1, 1);
	case PAINTPAL_03_1: return CreateMapCell(J_GRASS_IN_GREEN, K_BROKEN_STELE_MOSS, E_NONE, 1, 1);
	case PAINTPAL_03_2: return CreateMapCell(J_GRASS_IN_GREEN, K_NONE, E_NONE);
	case PAINTPAL_04_1: return CreateMapCell(J_GREEN, K_NONE, E_ITEM_00 + 0);
	case PAINTPAL_04_2: return CreateMapCell(J_GREEN, K_NONE, E_ITEM_00 + 1);
//	case PAINTPAL_05_1:
//	case PAINTPAL_05_2:
	case PAINTPAL_06_1: return CreateMapCell(J_FLOWER_IN_GREEN, K_NONE, E_ITEM_00 + 2);
	case PAINTPAL_06_2: return CreateMapCell(J_FLOWER_IN_GREEN, K_NONE, E_NONE);
	case PAINTPAL_07_1: return CreateMapCell(J_GREEN, K_WOOD, E_NONE, 1, 1);
	case PAINTPAL_07_2: return CreateMapCell(J_GREEN, K_NONE, E_NONE);
	case PAINTPAL_08_1: return CreateMapCell(J_WATER_IN_GREEN, E_NONE, E_NONE, 1);
//	case PAINTPAL_08_2:
//	case PAINTPAL_09_1:
//	case PAINTPAL_09_2:
//	case PAINTPAL_10_1:
//	case PAINTPAL_10_2:

	default:
		return CreateMapCell(J_ERROR, K_NONE, E_NONE, 0, 0);
	}
}

// ----

MapCell_t *(*GetMapCellLoader(int mapId))(int color)
{
	switch(mapId)
	{
	case 0: return MCL_Forest; break;

		/*
			<- ‚±‚±‚É’Ç‰Á
		*/

	default:
		error();
	}
	error(); // 2bs
	return NULL; // dummy
}
