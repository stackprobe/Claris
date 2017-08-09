#include "all.h"

PlayerShot_t *CreatePlayerShot(int kind, double x, double y, double xAdd, double yAdd, int subVal)
{
	PlayerShot_t *i = nb(PlayerShot_t);

	i->Kind = kind;
	i->X = x;
	i->Y = y;
	i->XAdd = xAdd;
	i->YAdd = yAdd;
	i->SubVal = subVal;

	// <-- ctor params

	i->Frame = -1;
	
	PlayerShotPosChanged(i);

	return i;
}
void ReleasePlayerShot(PlayerShot_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

/*
	以下が変更されたら呼ぶこと。
		i->X
		i->Y
*/
void PlayerShotPosChanged(PlayerShot_t *i)
{
	i->IX = d2i(i->X);
	i->IY = d2i(i->Y);
}

// <-- accessor

static int PSCrashEffectDerIdList[PSK_MAX] =
{
	D_BTLEFFECT055_00,
	D_BTLEFFECT052_00,
	D_BTLEFFECT054_00,
	D_BTLEFFECT053_00,
};

static void PSBound_Point(PlayerShot_t *i, int rx, int ry, int bxs, int bys, int &crashFrame)
{
	int fld_x = i->IX + rx;
	int fld_y = i->IY + ry;

	/*
		(fld_x, fld_y) < 0 のとき 0 になるけど、まあいいや。
	*/
	int map_x = fld_x / MAPCELL_W;
	int map_y = fld_y / MAPCELL_H;

	if(GDc.Map->RefCell(map_x, map_y, GDc.CommonMapCell)->TamaWallFlag) // ? 壁の中
	{
		if(bxs) i->XAdd = abs(i->XAdd) * bxs;
		if(bys) i->YAdd = abs(i->YAdd) * bys;

		crashFrame++;

		if(crashFrame == 1) // バウンドした。
		{
			CEE.EndPicId = PSCrashEffectDerIdList[i->Kind] + 9 | DTP;
			CEE.BlendAddOn = 1;
			AddCommonEffect(
				Gnd.EL,
				0,
				PSCrashEffectDerIdList[i->Kind] | DTP,
				fld_x,
				fld_y,
				0.0,
				0.25,
				0.5
				);
			CEE_Reset();
		}
	}
	else
		crashFrame = 0;
}
static void PSBound(PlayerShot_t *i)
{
	const int PS_R = 10;

	PSBound_Point(i,     0,  PS_R,  0, -1, i->u.Bounce.CrashFrame2);
	PSBound_Point(i, -PS_R,     0,  1,  0, i->u.Bounce.CrashFrame4);
	PSBound_Point(i,  PS_R,     0, -1,  0, i->u.Bounce.CrashFrame6);
	PSBound_Point(i,     0, -PS_R,  0,  1, i->u.Bounce.CrashFrame8);
}
int PlayerShotEachFrame(PlayerShot_t *i) // ret: ? dead
{
	i->X += i->XAdd;
	i->Y += i->YAdd;

	if(IsOutOfField_PS(i))
		return 1;

	PlayerShotPosChanged(i);

	double real_x = i->X;
	double real_y = i->Y;
	int deadFlag = 0;

	switch(i->Kind)
	{
	case PSK_NORMAL:
		break;

	case PSK_WAVE:
		{
			const double EXTEND = 20.0;
			double xa = i->YAdd * EXTEND;
			double ya = i->XAdd * EXTEND;

			if(i->SubVal)
				xa *= -1.0; // 左に回転
			else
				ya *= -1.0; // 右に回転

			double aRate = sin(i->Frame / 20.0);

			xa *= aRate;
			ya *= aRate;

			real_x += xa;
			real_y += ya;
		}
		break;

	case PSK_SPREAD:
		break;

	case PSK_BOUNCE:
		{
			int &remBndCnt = i->SubVal;

			int oldDir = GetDir(i->XAdd, i->YAdd);
			PSBound(i);
			int newDir = GetDir(i->XAdd, i->YAdd);

			if(oldDir + newDir == 44) // ? 真逆の方向に跳ね返った。
				remBndCnt = 0;

			int bounded = 0;

			if(
				i->u.Bounce.CrashFrame2 == 1 ||
				i->u.Bounce.CrashFrame4 == 1 ||
				i->u.Bounce.CrashFrame6 == 1 ||
				i->u.Bounce.CrashFrame8 == 1
				)
				bounded = 1;

			if(bounded)
			{
				switch(GetDir(i->XAdd, i->YAdd))
				{
				case 12:
				case 32:
				case 21:
				case 23:
					remBndCnt = 0;
					break;

				default:
					m_countDown(remBndCnt);
					break;
				}

				if(!remBndCnt) // ? 消滅
				{
					deadFlag = 1;
				}
				else // ? バウンドした。
				{
					1; // PSBound() へ移動した。
				}
			}
		}
		break;

	default:
		error();
	}

	int real_ix = d2i(real_x);
	int real_iy = d2i(real_y);

	switch(i->Kind)
	{
	case PSK_NORMAL:
	case PSK_WAVE:
	case PSK_SPREAD:
		{
			int map_x = real_ix / MAPCELL_W;
			int map_y = real_iy / MAPCELL_H;

			if(GDc.Map->GetCell(map_x, map_y)->TamaWallFlag) // ? 消滅
			{
				deadFlag = 1;
			}
		}
		break;

	case PSK_BOUNCE:
		break;

	default:
		error();
	}
	if(deadFlag) // 消滅
	{
		CEE.EndPicId = PSCrashEffectDerIdList[i->Kind] + 9 | DTP;
		CEE.BlendAddOn = 1;
		AddCommonEffect(
			Gnd.EL,
			0,
			PSCrashEffectDerIdList[i->Kind] | DTP,
			real_x,
			real_y,
			0.0,
			0.5,
			0.5
			);
		CEE_Reset();

		return 1;
	}

	{
		int dr_x = real_ix - GDc.ICameraX;
		int dr_y = real_iy - GDc.ICameraY;

		DPE.TL = GDc.DP;
		DPE_SetAlpha(0.2);
		DrawBegin(P_MAHOUJIN, dr_x, dr_y);
		DrawRotate(i->Frame / 10.0);
		DrawZoom(0.5);
		DrawEnd();
		DPE_Reset();

		DPE.TL = GDc.DP;
		DrawBegin(GetIconPicId(3 - i->Kind, 19), dr_x, dr_y);
		DrawRotate(i->Frame / 2.0);
		DrawEnd();
		DPE_Reset();
	}

	return 0;
}
void AllPlayerShotEachFrame(void)
{
	for(int index = 0; index < GDc.PlayerShotList->GetCount(); index++)
	{
		PlayerShot_t *i = GDc.PlayerShotList->GetElement(index);

		i->Frame++; // 0 ～

		if(PlayerShotEachFrame(i)) // ? dead
		{
			ReleasePlayerShot(i);
			GDc.PlayerShotList->SetElement(index, NULL);
		}
	}
	GDc.PlayerShotList->MultiDiscard(isPointNull);
}

static void AddPlayerShot(PlayerShot_t *i) // i: bind
{
	GDc.PlayerShotList->AddElement(i);
}
static void ShotByPlayer(int kind, double speed, int dir, double dirRot, int subVal)
{
	double nanameSpeed = speed / ROOT_2;
	double xa = 0.0;
	double ya = 0.0;

	switch(dir)
	{
	case 2: ya =  speed; break;
	case 4: xa = -speed; break;
	case 6: xa =  speed; break;
	case 8: ya = -speed; break;

	case 1:
		xa = -nanameSpeed;
		ya =  nanameSpeed;
		break;

	case 3:
		xa = nanameSpeed;
		ya = nanameSpeed;
		break;

	case 7:
		xa = -nanameSpeed;
		ya = -nanameSpeed;
		break;

	case 9:
		xa =  nanameSpeed;
		ya = -nanameSpeed;
		break;

	default:
		error();
	}

	rotatePos(dirRot, xa, ya);

	AddPlayerShot(CreatePlayerShot(kind, GDc.Player.X, GDc.Player.Y, xa, ya, subVal));
}
void PlayerShotProc(void)
{
	int pskFrame = GDc.Player.PSKFrame;
	int shotFrame = GDc.Player.ShotFrame;
	int shotCycle;

	switch(GDc.PSKind)
	{
	case PSK_NORMAL: shotCycle = 10; break;
	case PSK_WAVE:   shotCycle = 20; break;
	case PSK_SPREAD: shotCycle = 10; break;
	case PSK_BOUNCE: shotCycle = 25; break;

	default:
		error();
	}
	if(30 <= pskFrame && shotFrame && shotFrame % shotCycle == 0)
	{
		switch(GDc.PSKind)
		{
		case PSK_NORMAL:
			ShotByPlayer(PSK_NORMAL, 10.0, GDc.Player.Dir, 0.0, -1);
			break;

		case PSK_WAVE:
			ShotByPlayer(PSK_WAVE, 5.5, GDc.Player.Dir, 0.0, shotFrame / shotCycle % 2);
			break;

		case PSK_SPREAD:
			{
				for(int c = -2; c <= 2; c++)
				{
					ShotByPlayer(PSK_SPREAD, 10.0, GDc.Player.Dir, 0.3 * c, -1);
				}
			}
			break;

		case PSK_BOUNCE:
			{
				int dirL = RotDir(GDc.Player.Dir, -1);
				int dirM = GDc.Player.Dir;
				int dirR = RotDir(GDc.Player.Dir, 1);

				ShotByPlayer(PSK_BOUNCE, 8.0, dirL, 0.0, 4);
				ShotByPlayer(PSK_BOUNCE, 8.0, dirM, 0.0, 4);
				ShotByPlayer(PSK_BOUNCE, 8.0, dirR, 0.0, 4);
			}
			break;
		}
	}
}
