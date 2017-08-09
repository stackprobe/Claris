#include "all.h"

GDc_t GDc;

void GameInit(void)
{
	zeroclear(&GDc);

	GDc.DE = new taskList();
	GDc.DJ = new taskList();
	GDc.DK = new taskList();
	GDc.DP = new taskList();

	GDc.EnemyList = new autoList<Enemy_t *>();
	GDc.PlayerShotList = new autoList<PlayerShot_t *>();

	GDc.CommonMapCell = CreateMapCell(J_ERROR, K_NONE, E_NONE);
	GDc.PZScreen = CreateSubScreen(SCREEN_W, SCREEN_H, 1);
}
void GameFnlz(void)
{
	memFree(GDc.MapFile);
	delete GDc.MapFileData;
	delete GDc.Map;

	delete GDc.DE;
	delete GDc.DJ;
	delete GDc.DK;
	delete GDc.DP;

	releaseList(GDc.EnemyList, ReleaseEnemy);
	releaseList(GDc.PlayerShotList, ReleasePlayerShot);

	ReleaseMapCell(GDc.CommonMapCell);
	ReleaseSubScreen(GDc.PZScreen);

	zeroclear(&GDc);
}
