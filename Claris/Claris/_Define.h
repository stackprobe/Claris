/*
	ペイントのデフォルトのパレット
	PAINTPAL_<列数>_<行数>
*/
#define PAINTPAL_01_1 m_color(0, 0, 0)
#define PAINTPAL_01_2 m_color(255, 255, 255)
#define PAINTPAL_02_1 m_color(127, 127, 127)
#define PAINTPAL_02_2 m_color(195, 195, 195)
#define PAINTPAL_03_1 m_color(136, 0, 21)
#define PAINTPAL_03_2 m_color(185, 122, 87)
#define PAINTPAL_04_1 m_color(237, 28, 36)
#define PAINTPAL_04_2 m_color(255, 174, 201)
#define PAINTPAL_05_1 m_color(255, 127, 39)
#define PAINTPAL_05_2 m_color(255, 201, 14)
#define PAINTPAL_06_1 m_color(255, 242, 0)
#define PAINTPAL_06_2 m_color(239, 228, 176)
#define PAINTPAL_07_1 m_color(34, 177, 76)
#define PAINTPAL_07_2 m_color(181, 230, 29)
#define PAINTPAL_08_1 m_color(0, 162, 232)
#define PAINTPAL_08_2 m_color(153, 217, 234)
#define PAINTPAL_09_1 m_color(63, 72, 204)
#define PAINTPAL_09_2 m_color(112, 146, 190)
#define PAINTPAL_10_1 m_color(163, 73, 164)
#define PAINTPAL_10_2 m_color(200, 191, 231)

// ---- map chip ----

enum // TileId
{
	TILE_A1,
	TILE_A2,
	TILE_A3,
	TILE_A4,
	TILE_A5,
	TILE_B,
	TILE_C,
	TILE_D,
	TILE_E,

	TILE_MAX, // num of member
};

/*
	升のドット数
*/
#define MAPCELL_W 32
#define MAPCELL_H 32
/*
	升の数
*/
#define TILE_W 16
#define TILE_H 16

#define MINIMAPCELL_W (MAPCELL_W / 2)
#define MINIMAPCELL_H (MAPCELL_H / 2)
#define MINITILE_W (TILE_W * 2)
#define MINITILE_H (TILE_H * 2)

// ----

/*
	升の数
*/
#define MAP_W_MIN 25
#define MAP_H_MIN 19
#define MAP_W_MAX 5000
#define MAP_H_MAX 5000

#define ENEMY_OOS_MARGIN (SCREEN_H / 2) // Enemy Out-of-Screen Margin
#define PS_OOF_MARGIN (SCREEN_H / 2) // PlayerShot Out-of-Field Margin

#define P_MAHOUJIN (D_MAHOUJIN_HAJIKE_00 + 5 | DTP)
