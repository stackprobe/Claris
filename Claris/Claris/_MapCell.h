typedef struct MapCell_st
{
	int JimenId;  // �n��
	int KouzouId; // �n�ʂ̏�̍\����
	int EnemyId;  // ���̒n�ʂɂ���G
	/*
		CWF TWF
		--------
		0   0   ��ԁA�����Ȃ��n�ʂȂ�
		1   0   ����Ȃ�
		1   1   �ǂȂ�
		0   1   �����邯�ǒe��łĂȂ��A�e�������Ă���Ȃ��ꏊ
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
