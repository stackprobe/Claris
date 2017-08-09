#include "all.h"

Enemy_t *CreateEnemy(MapCell_t *owner, int enemyId, double x, double y, int subVal)
{
	errorCase(!owner);
	errorCase(enemyId < 0 || E_MAX <= enemyId);
	// x
	// y
	errorCase(subVal < -IMAX || IMAX < subVal);

	Enemy_t *i = nb(Enemy_t);

	i->Owner = owner;
	i->EnemyId = enemyId;
	i->X = x;
	i->Y = y;
	i->SubVal = subVal;

	// <-- ctor params

	i->Frame = -1;
	i->HP = -1;

	EnemyPosChanged(i);

	return i;
}
void ReleaseEnemy(Enemy_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

/*
	ˆÈ‰º‚ª•ÏX‚³‚ê‚½‚çŒÄ‚Ô‚±‚ÆB
		i->X
		i->Y
*/
void EnemyPosChanged(Enemy_t *i)
{
	i->IX = d2i(i->X);
	i->IY = d2i(i->Y);
}

// <-- accessor

void AllEnemyEachFrame(void)
{
	for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *e = GDc.EnemyList->GetElement(index);

		e->Frame++; // 0 `

		if(EnemyEachFrame(e)) // ? dead
		{
			GDc.EnemyList->SetElement(index, NULL);
			ReleaseEnemy(e);
		}
	}
	GDc.EnemyList->MultiDiscard((int (*)(Enemy_t **))isPointNull);
}
void LoadAllEnemy(void)
{
	for(int x = 0; x < GDc.Map->GetWidth(); x++)
	for(int y = 0; y < GDc.Map->GetHeight(); y++)
	{
		MapCell_t *mc = GDc.Map->GetCell(x, y);

		if(mc->EnemyId != E_NONE)
		{
			GDc.EnemyList->AddElement(LoadEnemy(mc, x, y));
		}
	}
}

int IsEnemyOutOfScreen(Enemy_t *i)
{
	return IsOutOfScreen(i->X, i->Y, ENEMY_OOS_MARGIN);
}
