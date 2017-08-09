enum // JimenId
{
	J_ERROR,
	J_GREEN,
	J_WATER_IN_GREEN,
	J_GRASS_IN_GREEN,
	J_FLOWER_IN_GREEN,

	J_MAX, // num of member
};

enum // KouzouId
{
	K_NONE,
	K_WOOD,
	K_WOOD_1,
	K_WOOD_3,
	K_WOOD_7,
	K_WOOD_9,
	K_WOOD_19,
	K_WOOD_37,
	K_BROKEN_STELE_T,
	K_BROKEN_STELE_B,
	K_BROKEN_STELE,
	K_BROKEN_STELE_MOSS,

	K_MAX, // num of member
};

enum // EnemyId
{
	E_NONE,
	E_START, // スタート地点
	ENUM_RANGE(E_ITEM_00, ITEM_NUM)

	E_MAX, // num of member
};

// ----

void DrawField(void);
