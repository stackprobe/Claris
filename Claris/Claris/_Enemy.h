typedef struct Enemy_st
{
	/*
		紐付く地面が無い場合は GDc.CommonMapCell とする。
		その場合 EnemyId != Owner->EnemyId であることに注意！
	*/
	MapCell_t *Owner;
	int EnemyId;
	double X;
	double Y;
	int SubVal;

	// <-- ctor params

	int Frame;
	/*
		-1 == 無敵, 自弾と接触ナシ, (敵弾, アイテムなど)
		0  == 無敵, 自弾と接触アリ
		0< == 破壊可能
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
		Item; // E_ITEM_00 〜 E_ITEM_00_END
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
