int GetMapCellPicId(int tileId, int x, int y);
int GetMiniMapCellPicId(int tileId, int x, int y);
int GetIconPicId(int x, int y);

/*
	Var_t *aTbl[3][3]
*/
template <class Var_t>
void GetAround(Var_t (*aTbl)[3], int x, int y, Var_t mcFltr(MapCell_t *))
{
	for(int rx = 0; rx < 3; rx++)
	for(int ry = 0; ry < 3; ry++)
	{
		aTbl[rx][ry] = mcFltr(GDc.Map->RefCell(x - 1 + rx, y - 1 + ry, GDc.CommonMapCell));
	}
}

#define AROUND_SIZE_MIN 2
#define AROUND_SIZE_MAX 15

typedef struct Around_st
{
	MapCell_t *Map[AROUND_SIZE_MAX][AROUND_SIZE_MAX];

	/*
		中心からの相対位置, ドット単位, -16 ～ 15
	*/
	i2D_t Pos;

	/*
		Map[0][0] の GDc.Map 上の座標, マップセル単位
	*/
	i2D_t MapPos;
}
Around_t;

void GetAround(Around_t *around, int x, int y, int size);
int GetDir(double x, double y);

int IsOutOfField(double x, double y, double margin = 0.0);
int IsOutOfField_PS(PlayerShot_t *i, double margin = PS_OOF_MARGIN);
