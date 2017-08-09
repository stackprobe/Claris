#include "all.h"

MapCell_t *CreateMapCell(int jimenId, int kouzouId, int enemyId, int charaWallFlag, int tamaWallFlag)
{
	errorCase(!m_isRange(jimenId, 0, J_MAX));
	errorCase(!m_isRange(kouzouId, 0, K_MAX));
	errorCase(!m_isRange(enemyId, 0, E_MAX));
	// charaWallFlag
	// tamaWallFlag

	MapCell_t *i = nb(MapCell_t);

	i->JimenId = jimenId;
	i->KouzouId = kouzouId;
	i->EnemyId = enemyId;
	i->CharaWallFlag = charaWallFlag;
	i->TamaWallFlag = tamaWallFlag;

	return i;
}
void ReleaseMapCell(MapCell_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

// <-- accessor
