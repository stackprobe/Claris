#include "all.h"

static void DrawWall(void)
{
	{
		int RAF_W = 260;
		int RAF_H = 582;
		int frm = ActFrame % RAF_W;

		for(int x = frm ? -RAF_W + frm : 0; x < SCREEN_W; x += RAF_W)
		{
			int sy = -x;

			while(0 < sy)
			{
				sy -= RAF_H;
			}
			for(int y = sy; y < SCREEN_H; y += RAF_H)
			{
				DPE.PicRes = GetInvPicRes();
				DrawSimple(D_ACTOR83_RAF_01 | DTP, x, y);
				DPE_Reset();
			}
		}
	}

	{
		const int MARGIN = 50;

		DPE_SetAlpha(0.9);
		DPE_SetBright(0.2, 0.2, 0.3);
		DrawRect(P_WHITEBOX, MARGIN, MARGIN, SCREEN_W - MARGIN * 2, SCREEN_H - MARGIN * 2);
		DPE_Reset();
	}

	// Face
	{
		DPE_SetBright(0.3, 0.5, 1.0);
		DrawRect(P_WHITEBOX, 60, 60, 116, 116);
		DPE_SetBright(0.8, 0.9, 1.0);
		DrawRect(P_WHITEBOX, 70, 70, 96, 96);
		DPE_Reset();
		DrawSimple(D_ACTOR83_FACE_00 + 7 | DTP, 70, 70);
	}
}

void PauseMain(void)
{
	FreezeInput();
	ActFrame = 0;

	for(; ; )
	{
		if(GetInput(INP_PAUSE) == 1)
		{
			break;
		}

		DrawWall();

		EachFrame();
	}

	FreezeInput();
	ActFrame = 0;
}
