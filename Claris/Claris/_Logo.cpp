#include "all.h"

void Logo(void)
{
	forscene(30)
	{
		DPE_SetBright(0.0, 0.0, 0.0);
		DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, SCREEN_H);
		DPE_Reset();

		EachFrame();
	}
	sceneLeave();

	const double Z_RATE = 0.93;
	double z = 1.2;

	forscene(60)
	{
		DPE_SetBright(0.0, 0.0, 0.0);
		DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, SCREEN_H);
		DPE_Reset();

		DPE_SetAlpha(sc_rate);
		DrawBegin(P_COPYRIGHT, SCREEN_CENTER_X, SCREEN_CENTER_Y);
		DrawZoom(z);
		DrawEnd();
		DPE_Reset();

		DPE_SetAlpha((1.0 - sc_rate) * 0.2);
		DrawBegin(P_COPYRIGHT, SCREEN_CENTER_X, SCREEN_CENTER_Y);
		DrawZoom(1.0 / z);
		DrawEnd();
		DPE_Reset();

		DPE_SetAlpha((1.0 - sc_rate) * 0.3);
		DrawBegin(P_COPYRIGHT, SCREEN_CENTER_X, SCREEN_CENTER_Y);
		DrawZoom(1.5 / z);
		DrawEnd();
		DPE_Reset();

		m_approach(z, 1.0, Z_RATE);

		EachFrame();
	}
	sceneLeave();

	__int64 lpBgnTm = GetCurrTime();

	forscene(90)
	{
		if(lpBgnTm + 1500 < GetCurrTime())
		{
LOG("[lpBgnTm-OF] %u\n", sc_numer);
			break;
		}
		if(sc_numer == 10)
		{
SW_Start();
			MusicTouch(MUS_TITLE);
SW_End();
		}
		DPE_SetBright(0.0, 0.0, 0.0);
		DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, SCREEN_H);
		DPE_Reset();

		DrawCenter(P_COPYRIGHT, SCREEN_CENTER_X, SCREEN_CENTER_Y);

		EachFrame();
	}
	sceneLeave();
	forscene(60)
	{
		DPE_SetBright(0.0, 0.0, 0.0);
		DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, SCREEN_H);
		DPE_Reset();

		DPE_SetAlpha(1.0 - sc_rate);
		DrawBegin(P_COPYRIGHT, SCREEN_CENTER_X, SCREEN_CENTER_Y);
		DrawZoom(z);
		DrawEnd();
		DPE_Reset();

		EachFrame();
	}
	sceneLeave();
}
