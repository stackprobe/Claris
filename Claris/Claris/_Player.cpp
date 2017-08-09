#include "all.h"

/*
	à»â∫ÇïœçXÇµÇΩÇÁåƒÇ‘Ç±Ç∆ÅB
		GDc.Player.X
		GDc.Player.Y
*/
void PlayerPosChanged(void)
{
	GDc.Player.IX = d2i(GDc.Player.X);
	GDc.Player.IY = d2i(GDc.Player.Y);
}
void DrawPlayer(void)
{
	int dirIdx;

	switch(GDc.Player.Dir)
	{
	case 2: dirIdx = 0; break;
	case 4: dirIdx = 1; break;
	case 6: dirIdx = 2; break;
	case 8: dirIdx = 3; break;
	case 1: dirIdx = 16; break;
	case 3: dirIdx = 18; break;
	case 7: dirIdx = 17; break;
	case 9: dirIdx = 19; break;

	default:
		error();
	}
	int animeFrm = 1;

	if(GDc.Player.MoveFrame)
	{
		animeFrm = (ActFrame / 5) % 4;

		if(animeFrm == 3)
			animeFrm = 1;
	}

	DPE.TL = GDc.DP;
	DrawCenter(
		D_ACTOR83_00 + dirIdx * 3 + animeFrm | DTP,
		GDc.Player.IX - GDc.ICameraX,
		GDc.Player.IY - GDc.ICameraY
		);
	DPE_Reset();
}
