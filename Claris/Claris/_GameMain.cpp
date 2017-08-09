#include "all.h"

static void FollowCamera(double followRate = 0.85)
{
	double targetX = GDc.Player.X - SCREEN_W / 2.0;
	double targetY = GDc.Player.Y - SCREEN_H / 2.0;

	m_range(targetX, 0.0, GDc.Field_W - SCREEN_W);
	m_range(targetY, 0.0, GDc.Field_H - SCREEN_H);

	m_approach(GDc.CameraX, targetX, followRate);
	m_approach(GDc.CameraY, targetY, followRate);

	GDc.ICameraX = d2i(GDc.CameraX);
	GDc.ICameraY = d2i(GDc.CameraY);

	m_range(GDc.ICameraX, 0, d2i(GDc.Field_W) - SCREEN_W); // 2bs
	m_range(GDc.ICameraY, 0, d2i(GDc.Field_H) - SCREEN_H); // 2bs

	CameraX = (double)GDc.ICameraX;
	CameraY = (double)GDc.ICameraY;
}

static void SPEP_Around(int l, int t, int w, int h, int initDir)
{
	i2D_t p1 = { -1, -1 };
	i2D_t p2 = { -1, -1 };

	for(int x = l; x < l + w; x++)
	for(int y = t; y < t + h; y++)
	{
		MapCell_t *mc = GDc.Map->GetCell(x, y);

		if(!mc->CharaWallFlag) // ? 通路
		{
			if(p1.X == -1)
			{
				p1.X = x;
				p1.Y = y;
			}
			p2.X = x;
			p2.Y = y;
		}
	}
	GDc.Player.X = (p1.X + p2.X + 1) * MAPCELL_W / 2.0;
	GDc.Player.Y = (p1.Y + p2.Y + 1) * MAPCELL_H / 2.0;
	GDc.Player.Dir = initDir;
}
static void SetPlayerEntryPos(void)
{
	switch(GDc.EntryDir)
	{
	case 0: // E_START
		{
			for(int x = 0; x < GDc.Map->GetWidth(); x++)
			for(int y = 0; y < GDc.Map->GetHeight(); y++)
			{
				MapCell_t *mc = GDc.Map->GetCell(x, y);

				if(mc->EnemyId == E_START)
				{
					GDc.Player.X = x * MAPCELL_W + MAPCELL_W / 2;
					GDc.Player.Y = y * MAPCELL_H + MAPCELL_H / 2;
					GDc.Player.Dir = 2;

					return;
				}
			}
			error(); // E_START not found
		}
		break;

	case 2: // 下(上向き)
		SPEP_Around(
			0,
			GDc.Map->GetHeight() - 1,
			GDc.Map->GetWidth(),
			1,
			8
			);
		break;

	case 4: // 左(右向き)
		SPEP_Around(
			0,
			0,
			1,
			GDc.Map->GetHeight(),
			6
			);
		break;

	case 6: // 右(左向き)
		SPEP_Around(
			GDc.Map->GetWidth() - 1,
			0,
			1,
			GDc.Map->GetHeight(),
			4
			);
		break;

	case 8: // 上(下向き)
		SPEP_Around(
			0,
			0,
			GDc.Map->GetWidth(),
			1,
			2
			);
		break;

	default:
		error();
	}

	PlayerPosChanged();
}

static void SetA2A3(void)
{
	GetAround(&GDc.A2, GDc.Player.IX, GDc.Player.IY, 2);
	GetAround(&GDc.A3, GDc.Player.IX, GDc.Player.IY, 3);
}
static void XTurnA2(void)
{
	GDc.A2.Pos.X *= -1;
	t_swap(GDc.A2.Map[0][0], GDc.A2.Map[1][0]);
	t_swap(GDc.A2.Map[0][1], GDc.A2.Map[1][1]);
}
static void YTurnA2(void)
{
	GDc.A2.Pos.Y *= -1;
	t_swap(GDc.A2.Map[0][0], GDc.A2.Map[0][1]);
	t_swap(GDc.A2.Map[1][0], GDc.A2.Map[1][1]);
}
/*
	これを呼び出す前に SetA2A3() を呼ぶこと。
	位置を補正しなければならない場合は GDc.A2.Pos を変更する。
*/
static void PlayerKabeProc(void)
{
	errorCase(!GDc.A2.Map[0][0]); // 2bs

	switch(
		(GDc.A2.Map[0][1]->CharaWallFlag ? 1 : 0) | // 1
		(GDc.A2.Map[1][1]->CharaWallFlag ? 2 : 0) | // 3
		(GDc.A2.Map[0][0]->CharaWallFlag ? 4 : 0) | // 7
		(GDc.A2.Map[1][0]->CharaWallFlag ? 8 : 0)   // 9
		)
	{
	case 0: // 壁なし
		break;

	case 15: // 壁の中
		{
			for(int x = 0; x < 3; x++)
			for(int y = 0; y < 3; y++)
			{
				if(!GDc.A3.Map[x][y]->CharaWallFlag)
				{
					GDc.A2.Pos.X += (x - 1) * 10;
					GDc.A2.Pos.Y += (y - 1) * 10;

					goto endFndNoWallInA3;
				}
			}
endFndNoWallInA3:;
		}
		break;

	case 1: // 左下のみ
	case 4: // 左上のみ
	case 5: // 左
	case 7: // 右上のみ空き
	case 13: // 右下のみ空き
		XTurnA2();
		PlayerKabeProc();
		XTurnA2();
		break;

	case 8: // 右上のみ
	case 9: // 右上と左下
	case 12: // 上
	case 14: // 左下のみ空き
		YTurnA2();
		PlayerKabeProc();
		YTurnA2();
		break;

	case 2: // 右下のみ
		{
			if(-16 < GDc.A2.Pos.X && -16 < GDc.A2.Pos.Y)
			{
				const int SLIDE_BORDER = 13;
				const int SLIDE_SPEED = 1;

				if(GDc.A2.Pos.X < GDc.A2.Pos.Y)
				{
					GDc.A2.Pos.X = -16;

					if(GDc.A2.Pos.Y <= SLIDE_BORDER)
					{
						GDc.A2.Pos.Y -= SLIDE_SPEED;
					}
				}
				else
				{
					GDc.A2.Pos.Y = -16;

					if(GDc.A2.Pos.X <= SLIDE_BORDER)
					{
						GDc.A2.Pos.X -= SLIDE_SPEED;
					}
				}
			}
		}
		break;

	case 10: // 右
		GDc.A2.Pos.X = -16;
		break;

	case 3: // 下
		GDc.A2.Pos.Y = -16;
		break;

	case 6: // 左上と右下
		{
			if(GDc.A2.Pos.X < GDc.A2.Pos.Y)
			{
				GDc.A2.Pos.X = -16;
				GDc.A2.Pos.Y = 16;
			}
			else
			{
				GDc.A2.Pos.X = 16;
				GDc.A2.Pos.Y = -16;
			}
		}
		break;

	case 11: // 左上のみ空き
		GDc.A2.Pos.X = -16;
		GDc.A2.Pos.Y = -16;
		break;

	default:
		error();
	}
}

void GameMain(void)
{
	// Load GDc.Map {

	if(!GDc.Map)
	{
		if(!GDc.MapFileData)
		{
			errorCase(m_isEmpty(GDc.MapFile));

			GDc.MapFileData = readFile(GDc.MapFile);
		}
		GDc.Map = LoadMap(GetMapCellLoader(GDc.MapId), GDc.MapFileData);
	}
	errorCase(!m_isRange(GDc.Map->GetWidth(), MAP_W_MIN, MAP_W_MAX));
	errorCase(!m_isRange(GDc.Map->GetHeight(), MAP_H_MIN, MAP_H_MAX));

	LoadMapRegist(GDc.Map, GDc.MapId);

	// }

	GDc.Field_W = GDc.Map->GetWidth() * MAPCELL_W;
	GDc.Field_H = GDc.Map->GetHeight() * MAPCELL_H;

	LoadAllEnemy();

	ActFrame = 0;
	SetCurtain();
	FreezeInput();
	SetPlayerEntryPos();
	FollowCamera(0.0);

	// test
	{
		Around_t a;

		GetAround(&a, 60, 130, 2);

		errorCase(a.Map[0][0] != GDc.Map->GetCell(1, 3));
		errorCase(a.Pos.X != -4);
		errorCase(a.Pos.Y != 2);
		errorCase(a.MapPos.X != 1);
		errorCase(a.MapPos.Y != 3);

		GetAround(&a, 60, 130, 3);

		errorCase(a.Map[0][0] != GDc.Map->GetCell(0, 3));
		errorCase(a.Pos.X != 12);
		errorCase(a.Pos.Y != -14);
		errorCase(a.MapPos.X != 0);
		errorCase(a.MapPos.Y != 3);
	}

	for(; ; )
	{
		zeroclear(&GDc.FS);

		if(GetInput(INP_PAUSE) == 1)
		{
			PauseMain();
		}

		// Player
		{
			int dir2 = 1 <= GetInput(INP_DIR_2);
			int dir4 = 1 <= GetInput(INP_DIR_4);
			int dir6 = 1 <= GetInput(INP_DIR_6);
			int dir8 = 1 <= GetInput(INP_DIR_8);
			int dir; // 2468-1379-5

			     if(dir2 && dir4) dir = 1;
			else if(dir2 && dir6) dir = 3;
			else if(dir4 && dir8) dir = 7;
			else if(dir6 && dir8) dir = 9;
			else if(dir2) dir = 2;
			else if(dir4) dir = 4;
			else if(dir6) dir = 6;
			else if(dir8) dir = 8;
			else          dir = 5;

			int slow = 1 <= GetInput(INP_A);
			int fast = 1 <= GetInput(INP_R);

			if(Gnd.FastBtnReverseMode)
				fast = fast ? 0 : 1;

			double speed = 3.0;

			if(slow)
				speed -= 1.0;

			if(fast)
				speed += 2.0;

			double nanameSpeed = speed / ROOT_2;

			switch(dir)
			{
			case 2:
				GDc.Player.Y += speed;
				break;

			case 4:
				GDc.Player.X -= speed;
				break;

			case 6:
				GDc.Player.X += speed;
				break;

			case 8:
				GDc.Player.Y -= speed;
				break;

			case 1:
				GDc.Player.X -= nanameSpeed;
				GDc.Player.Y += nanameSpeed;
				break;

			case 3:
				GDc.Player.X += nanameSpeed;
				GDc.Player.Y += nanameSpeed;
				break;

			case 7:
				GDc.Player.X -= nanameSpeed;
				GDc.Player.Y -= nanameSpeed;
				break;

			case 9:
				GDc.Player.X += nanameSpeed;
				GDc.Player.Y -= nanameSpeed;
				break;

			case 5:
				break;

			default:
				error();
			}
			if(dir != 5 && !slow)
				GDc.Player.Dir = dir;

			if(dir != 5)
				GDc.Player.MoveFrame++;
			else
				GDc.Player.MoveFrame = 0;

			if(!GDc.Player.MoveFrame) // 停止したら座標を整数に矯正
			{
				GDc.Player.X = (double)d2i(GDc.Player.X);
				GDc.Player.Y = (double)d2i(GDc.Player.Y);
			}
			PlayerPosChanged();
		}

		// ? フィールドから出た。
		if(
			GDc.Player.X < 0.0 || GDc.Field_W <= GDc.Player.X ||
			GDc.Player.Y < 0.0 || GDc.Field_H <= GDc.Player.Y
			)
		{
			break;
		}

		{
			SetA2A3();
			i2D_t origA2Pos = GDc.A2.Pos;

			PlayerKabeProc();

			// ? GDc.A2.Pos が変更された。
			if(
				origA2Pos.X != GDc.A2.Pos.X ||
				origA2Pos.Y != GDc.A2.Pos.Y
				)
			{
				GDc.Player.X = (double)((GDc.A2.MapPos.X + 1) * MAPCELL_W + GDc.A2.Pos.X);
				GDc.Player.Y = (double)((GDc.A2.MapPos.Y + 1) * MAPCELL_H + GDc.A2.Pos.Y);

				PlayerPosChanged();
			}
		}

		// PlayerShot
		{
			int chgwpn = GetInput(INP_L) == 1;

			if(chgwpn)
			{
				GDc.PSKind = (GDc.PSKind + 1) % PSK_MAX;
				GDc.Player.PSKFrame = 0;
			}
			else
				GDc.Player.PSKFrame++;

			if(1 <= GetInput(INP_B))
				GDc.Player.ShotFrame++;
			else
				GDc.Player.ShotFrame = 0;

			PlayerShotProc();
		}

		FollowCamera();
		AllEnemyEachFrame();
		AllPlayerShotEachFrame();

		// Draw ...

		DrawField();
		DrawPlayer();

		GDc.DJ->ExecuteAllTask();
		GDc.DP->ExecuteAllTask();
		GDc.DE->ExecuteAllTask();
		GDc.DK->ExecuteAllTask();

		EachFrame();
	}

	FreezeInput();
	SaveMapRegist(GDc.Map, GDc.MapId);
}
