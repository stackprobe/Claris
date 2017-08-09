typedef struct GDc_st
{
	// Params {
	int MapId; // 0 - IMAX

	/*
		�ǂꂩ�P�͗L���ł��邱�ƁB
	*/
	char *MapFile; // bind
	autoList<uchar> *MapFileData; // bind
	autoTable<MapCell_t*> *Map; // bind

	/*
		0 - E_START
		2468 - �����E��(����)
	*/
	int EntryDir;
	int PSKind; // PSK_*
	// }

	// Return {
	// }

	double Field_W;
	double Field_H;

	/*
		for Draw
	*/
	taskList *DE; // DrawEnemy
	taskList *DJ; // DrawJimen
	taskList *DK; // DrawKouzou
	taskList *DP; // DrawPlayer

	autoList<Enemy_t *> *EnemyList;
	autoList<PlayerShot_t *> *PlayerShotList;

	struct
	{
		double X;
		double Y;
		int IX;
		int IY;
		int Dir; // 2468-1379
		int MoveFrame; // zd
		int PSKFrame; // ���݂� PSKind �ɕύX����Ă���̌o�߃t���[��
		int ShotFrame; // zd
	}
	Player;

	double CameraX;
	double CameraY;
	int ICameraX;
	int ICameraY;

	Around_t A2;
	Around_t A3;

	MapCell_t *CommonMapCell;
	SubScreen_t *PZScreen;

	/*
		�t���[�����[�v�̐擪�Ń[���N���A����B
	*/
	struct
	{
		int Dummy;
	}
	FS; // FrameStatus
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
