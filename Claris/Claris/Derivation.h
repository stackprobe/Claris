enum
{
	ENUM_RANGE(D_DUMMY_00, 4)

	// app >

	ENUM_RANGE(D_TITLEITEM_00, 4)
	ENUM_RANGE(D_ACTOR83_00, 3 * 4 * 5)
	ENUM_RANGE(D_ACTOR83_FACE_00, 4 * 2 * 2)

	ENUM_RANGE(D_TILE_00, TILE_MAX * TILE_W * TILE_H)
	ENUM_RANGE(D_MINITILE_00, TILE_MAX * MINITILE_W * MINITILE_H)

	ENUM_RANGE(D_ICONSET_00, 16 * 22)
	D_ACTOR83_RAF_00,
	D_ACTOR83_RAF_01,

	ENUM_RANGE(D_BTLEFFECT051_00, 10) // 白黒
	ENUM_RANGE(D_BTLEFFECT052_00, 10) // 赤？
	ENUM_RANGE(D_BTLEFFECT053_00, 10) // シアン
	ENUM_RANGE(D_BTLEFFECT054_00, 10) // 緑
	ENUM_RANGE(D_BTLEFFECT055_00, 10) // 黄色
	ENUM_RANGE(D_BTLEFFECT056_00, 10) // マゼンタ

	ENUM_RANGE(D_MAHOUJIN_HAJIKE_00, 14)

	// < app

	D_MAX, // num of member
};

typedef struct DerInfo_st
{
	int ParentPicId;
	int X;
	int Y;
	int W;
	int H;
}
DerInfo_t;

int Der(resCluster<PicInfo_t *> *resclu, int derId);
int Der_W(int derId);
int Der_H(int derId);

void UnloadAllDer(resCluster<PicInfo_t *> *resclu);
