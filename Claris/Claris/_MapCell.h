typedef struct MapCell_st
{
	int JimenId;  // 地面
	int KouzouId; // 地面の上の構造物
	int EnemyId;  // この地面にいる敵
	/*
		CWF TWF
		--------
		0   0   空間、何もない地面など
		1   0   水上など
		1   1   壁など
		0   1   歩けるけど弾を打てない、弾が入ってこれない場所
	*/
	int CharaWallFlag;
	int TamaWallFlag;

	// <-- ctor params

	struct
	{
		int Retired;
	}
	Regist;
}
MapCell_t;

MapCell_t *CreateMapCell(int jimenId, int kouzouId, int enemyId, int charaWallFlag = 0, int tamaWallFlag = 0);
void ReleaseMapCell(MapCell_t *i);

// <-- cdtor

// <-- accessor
