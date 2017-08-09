#include "all.h"

static int LMFF_IsWood(MapCell_t *mc)
{
	if(!mc)
		return 1;

	switch(mc->KouzouId)
	{
	case K_WOOD:
	case K_WOOD_1:
	case K_WOOD_3:
	case K_WOOD_7:
	case K_WOOD_9:
	case K_WOOD_19:
	case K_WOOD_37:
		return 1;
	}
	return 0;
}
static void LMFF_SetWoodPart(MapCell_t *mc, int kouzouId, int mltKouzouId)
{
	if(!mc)
		return;

	if(mc->KouzouId == K_WOOD)
		mc->KouzouId = kouzouId;
	else
		mc->KouzouId = mltKouzouId;
}
static void LM_ForestFltr(autoTable<MapCell_t *> *map)
{
	for(int s = -1; s <= 0; s++)
	for(int x = s; x <= map->GetWidth(); x += 2)
	for(int y = s; y <= map->GetHeight(); y += 2)
	{
		MapCell_t *mc7 = map->RefCell(x + 0, y + 0, NULL);
		MapCell_t *mc9 = map->RefCell(x + 1, y + 0, NULL);
		MapCell_t *mc1 = map->RefCell(x + 0, y + 1, NULL);
		MapCell_t *mc3 = map->RefCell(x + 1, y + 1, NULL);

		if(
			LMFF_IsWood(mc7) &&
			LMFF_IsWood(mc9) &&
			LMFF_IsWood(mc1) &&
			LMFF_IsWood(mc3)
			)
		{
			LMFF_SetWoodPart(mc7, K_WOOD_7, K_WOOD_37);
			LMFF_SetWoodPart(mc9, K_WOOD_9, K_WOOD_19);
			LMFF_SetWoodPart(mc1, K_WOOD_1, K_WOOD_19);
			LMFF_SetWoodPart(mc3, K_WOOD_3, K_WOOD_37);
		}
	}
}

// ----

autoTable<MapCell_t *> *LoadMap(MapCell_t *(*rgbToMapCell)(int color), autoList<uchar> *fileData)
{
	errorCase(!rgbToMapCell);
	errorCase(!fileData);

	autoTable<uint> *bmp = readBmpFile(fileData);
	autoTable<MapCell_t *> *map = new autoTable<MapCell_t *>((MapCell_t *(*)(void))getZero, ReleaseMapCell, bmp->GetWidth(), bmp->GetHeight());

	for(int x = 0; x < bmp->GetWidth(); x++)
	for(int y = 0; y < bmp->GetHeight(); y++)
	{
		map->PutCell(x, y, rgbToMapCell((int)bmp->GetCell(x, y)));
	}
	delete bmp;

	LM_ForestFltr(map);

	return map;
}
autoTable<MapCell_t *> *LoadMap_x(MapCell_t *(*rgbToMapCell)(int color), autoList<uchar> *fileData)
{
	autoTable<MapCell_t *> *map = LoadMap(rgbToMapCell, fileData);
	delete fileData;
	return map;
}
autoTable<MapCell_t *> *LoadMap(MapCell_t *(*rgbToMapCell)(int color), char *file)
{
	return LoadMap_x(rgbToMapCell, readFile(file));
}
