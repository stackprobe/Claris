typedef struct Enemy_st
{
	/*
		ïRïtÇ≠ínñ Ç™ñ≥Ç¢èÍçáÇÕ GDc.CommonMapCell Ç∆Ç∑ÇÈÅB
		ÇªÇÃèÍçá EnemyId != Owner->EnemyId Ç≈Ç†ÇÈÇ±Ç∆Ç…íçà”ÅI
	*/
	MapCell_t *Owner;
	int EnemyId;
	double X;
	double Y;
	int SubVal;

	// <-- ctor params

	int Frame;
	/*
		-1 == ñ≥ìG, é©íeÇ∆ê⁄êGÉiÉV, (ìGíe, ÉAÉCÉeÉÄÇ»Ç«)
		0  == ñ≥ìG, é©íeÇ∆ê⁄êGÉAÉä
		0< == îjâÛâ¬î\
	*/
	int HP;
	int IX;
	int IY;

	union
	{
		struct
		{
			int ItemId;
		}
		Item; // E_ITEM_00 Å` E_ITEM_00_END
	}
	u;
}
Enemy_t;

Enemy_t *CreateEnemy(MapCell_t *owner, int enemyId, double x, double y, int subVal = -1);
void ReleaseEnemy(Enemy_t *i);

// <-- cdtor

void EnemyPosChanged(Enemy_t *i);

// <-- accessor

void AllEnemyEachFrame(void);
void LoadAllEnemy(void);

int IsEnemyOutOfScreen(Enemy_t *i);
