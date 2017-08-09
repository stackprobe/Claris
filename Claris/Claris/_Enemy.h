typedef struct Enemy_st
{
	/*
		�R�t���n�ʂ������ꍇ�� GDc.CommonMapCell �Ƃ���B
		���̏ꍇ EnemyId != Owner->EnemyId �ł��邱�Ƃɒ��ӁI
	*/
	MapCell_t *Owner;
	int EnemyId;
	double X;
	double Y;
	int SubVal;

	// <-- ctor params

	int Frame;
	/*
		-1 == ���G, ���e�ƐڐG�i�V, (�G�e, �A�C�e���Ȃ�)
		0  == ���G, ���e�ƐڐG�A��
		0< == �j��\
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
		Item; // E_ITEM_00 �` E_ITEM_00_END
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
