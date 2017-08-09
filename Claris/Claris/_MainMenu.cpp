/*
	メニューの位置
		SetPrint(60, 310 - 20 * (行数), 40);
*/

#include "all.h"

static void DrawTitleWall(void)
{
	double dx = cos(ActFrame / 199.0) * 40.0;
	double dy = cos(ActFrame / 211.0) * 30.0;

	DrawBegin(P_TITLEWALL, SCREEN_CENTER_X + dx, SCREEN_CENTER_Y + dy);
	DrawZoom(1.1);
	DrawEnd();

	if(dRnd() < 0.03 + sin(ActFrame / 307.0) * 0.02)
	{
		CEE.Z_B = 1.1;
		CEE.SlideX = dx;
		CEE.SlideY = dy;
		AddCommonEffect(
			Gnd.EL, 1, P_TITLEWALL,
			SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0, 1.0, 0.3,
			eRnd() * 0.1,
			eRnd() * 0.1,
			dRnd() < 0.1 ? eRnd() * 0.0015 : 0.0,
			eRnd() * 0.0003 + 0.0001,
			-0.001 - dRnd() * 0.001
			);
		CEE_Reset();
	}
	Gnd.EL->ExecuteAllTask();

	double titleX = 560.0 + dx * 0.4;
	double titleY = 300.0 + dy * 0.4;

	double tba = 0.5 + sin(ActFrame / 103.0) * 0.185 + sin(ActFrame / 3.0) * 0.015 * sin(ActFrame / 107.0);
	double tfa = 0.3;

	ifsceneBegin(300, ActFrame)
	{
		DPE_SetBlendAdd(tba * sc_rate);
		DrawCenter(P_TITLE, titleX, titleY);
		DPE_Reset();
	}
	ifsceneEnd
	{
		DPE_SetBlendAdd(tba);
		DrawCenter(P_TITLE, titleX, titleY);
		DPE_Reset();
	}
	sceneLeave();

	ifsceneBegin(700, ActFrame)
	{
		DPE_SetAlpha(tfa * sc_rate);
		DrawCenter(P_TITLE, titleX, titleY);
		DPE_Reset();
	}
	ifsceneEnd
	{
		DPE_SetAlpha(tfa);
		DrawCenter(P_TITLE, titleX, titleY);
		DPE_Reset();
	}
	sceneLeave();
}
static void DrawTitleWall_Curtain(void)
{
	DrawTitleWall();
	CurtainEachFrame();
}

// ---- SettingMenu ----

static int SM_GetPressPadBtnId(void)
{
	int padId = Gnd.PrimaryPadId;

	if(padId == -1) // ? 未定義
		padId = 0; // 適当なデフォ

	for(int btnId = 0; btnId < PAD_BUTTON_MAX; btnId++)
	{
		if(GetPadInput(padId, btnId) == 1)
		{
			return btnId;
		}
	}
	return -1; // not found
}
static void SM_PadConfig(void)
{
	int *pPadBtns[] =
	{
		&Gnd.PadBtnId.Dir_8,
		&Gnd.PadBtnId.Dir_2,
		&Gnd.PadBtnId.Dir_4,
		&Gnd.PadBtnId.Dir_6,
		&Gnd.PadBtnId.A,
		&Gnd.PadBtnId.B,
		&Gnd.PadBtnId.L,
		&Gnd.PadBtnId.R,
		&Gnd.PadBtnId.Pause,
	};
	char *btnNames[] =
	{
		"上",
		"下",
		"左",
		"右",
		"方向ロック／決定",
		"攻撃／キャンセル",
		"武器切り替え",
		"高速移動",
		"ポーズ",
	};
	errorCase(lengthof(pPadBtns) != lengthof(btnNames));
	int btnMax = lengthof(pPadBtns);
	int btnIndex = 0;
	void *backup = memClone(&Gnd.PadBtnId, sizeof(Gnd.PadBtnId));

	FreezeInput();
	UnassignAllPadBtnId();

	while(btnIndex < btnMax)
	{
		if(
			GetKeyInput(KEY_INPUT_Z) == 1 ||
			GetKeyInput(KEY_INPUT_X) == 1
			)
		{
			memcpy(&Gnd.PadBtnId, backup, sizeof(Gnd.PadBtnId)); // 復元
			break;
		}

		{
			int btnId = SM_GetPressPadBtnId();

			if(btnId != -1)
			{
				for(int index = 0; index < btnIndex; index++)
					if(*pPadBtns[index] == btnId) // ? 重複
						goto endPutPadBtnId;

				*pPadBtns[btnIndex] = btnId;
				btnIndex++;
			}
endPutPadBtnId:;
		}

		DrawTitleWall_Curtain();

		PE_Border(GetColor(0, 100, 0));
		SetPrint(60, 50, 40);
		Print("パッドのボタン設定");
		PrintRet();

		for(int index = 0; index < btnMax; index++)
		{
			Print_x(xcout("[%c] %sボタン", index == btnIndex ? '>' : ' ', btnNames[index]));

			if(index < btnIndex)
			{
				Print_x(xcout(" -> %d", *pPadBtns[index]));
			}
			PrintRet();
		}
		PrintRet();
		Print("# カーソルが指すボタンを押して下さい。");
		PrintRet();
		Print("# ＺキーまたはＸキーを押すとキャンセルします。");
		PE_Reset();

		EachFrame();
	}
	FreezeInput();

	memFree(backup);
}
static void SM_WindowSizeSetting(void)
{
	const int selectMax = 12;
	int selectIndex = 0;

	FreezeInput();

	for(; ; )
	{
		if(GetPound(INP_DIR_8))
			selectIndex--;

		if(GetPound(INP_DIR_2))
			selectIndex++;

		if(GetPound(INP_B))
		{
			if(selectIndex == selectMax - 1)
				break;

			selectIndex = selectMax - 1;
		}
		m_range(selectIndex, 0, selectMax - 1);

		if(GetPound(INP_A))
		{
			switch(selectIndex)
			{
			case 0: SetScreenSize(800, 600); break;
			case 1: SetScreenSize(900, 675); break;
			case 2: SetScreenSize(1000, 750); break;
			case 3: SetScreenSize(1100, 825); break;
			case 4: SetScreenSize(1200, 900); break;
			case 5: SetScreenSize(1300, 975); break;
			case 6: SetScreenSize(1400, 1050); break;
			case 7: SetScreenSize(1500, 1125); break;
			case 8: SetScreenSize(1600, 1200); break;
			case 9:
				SetScreenSize(
					GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN)
					);
				break;

			case 10:
				{
					int w = GetSystemMetrics(SM_CXSCREEN);
					int h = GetSystemMetrics(SM_CYSCREEN);

					if(w * SCREEN_H < h * SCREEN_W) // 縦長モニタ -> 横幅に合わせる
					{
						h = d2i(((double)w * SCREEN_H) / SCREEN_W);
					}
					else // 横長モニタ -> 縦幅に合わせる
					{
						w = d2i(((double)h * SCREEN_W) / SCREEN_H);
					}
					SetScreenSize(w, h);
				}
				break;

			case 11:
				goto endMenu;

			default:
				error();
			}
		}
		DrawTitleWall_Curtain();

		PE_Border(GetColor(0, 100, 0));
		SetPrint(60, 50, 40);
		Print("ウィンドウサイズの設定");
		PrintRet();
		int c = 0;
		Print_x(xcout("[%c]　800 x 600 (デフォルト)", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　900 x 675", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1000 x 750", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1100 x 825", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1200 x 900", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1300 x 975", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1400 x 1050", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1500 x 1125", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　1600 x 1200", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　モニターのサイズに合わせる", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　縦横比を維持してモニターのサイズに合わせる", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　戻る", selectIndex == c++ ? '>' : ' '));
		PE_Reset();

		EachFrame();
	}
endMenu:
	FreezeInput();
}
static void SM_VolumeSetting(int seMode)
{
	const int VOL_MAX = 680;
	const int VOL_DEF = d2i(DEFAULT_VOLUME * VOL_MAX);
	double dvol = seMode ? Gnd.SEVolume : Gnd.MusicVolume;
	int volume = d2i(dvol * VOL_MAX);
	int lastvol = volume;

	FreezeInput();

	for(; ; )
	{
		if(GetPound(INP_DIR_4))
			volume -= 10;

		if(GetPound(INP_DIR_6))
			volume += 10;

		if(GetPound(INP_DIR_2))
			volume--;

		if(GetPound(INP_DIR_8))
			volume++;

		if(GetPound(INP_B))
		{
			if(volume == VOL_DEF)
				break;

			volume = VOL_DEF;
		}
		m_range(volume, 0, VOL_MAX);

		if(GetPound(INP_A))
			break;

		if(lastvol != volume)
		{
			if(seMode)
			{
				Gnd.SEVolume = (double)volume / VOL_MAX;
				UpdateSEVolume();
			}
			else
			{
				Gnd.MusicVolume = (double)volume / VOL_MAX;
				UpdateMusicVolume();
			}
			lastvol = volume;
		}
		if(seMode && ProcFrame % 60 == 0)
		{
			SEPlay(SE_GET);
		}
		DrawTitleWall_Curtain();

		PE_Border(GetColor(0, 100, 0));
		SetPrint(60, 170, 40);
		Print_x(xcout("%sボリューム設定", seMode ? "ＳＥ" : "ＢＧＭ"));
		PrintRet();
		PrintRet();
		Print_x(xcout("[ %.5f ]", (double)volume / VOL_MAX));
		PrintRet();
		PrintRet();
		Print("# 上下左右: ボリューム変更");
		PrintRet();
		Print("# キャンセル: デフォルトの音量");
		PrintRet();
		Print("# 決定: 戻る");
		PE_Reset();

		{
			const int dr_l = 60;
			const int dr_t = 210;
			const int dr_w = 680;
			const int dr_h = 20;

			DPE_SetAlpha(0.5);
			DPE_SetBright(0, 0, 0);
			DrawRect(P_WHITEBOX, dr_l, dr_t, dr_w, dr_h);

			if(volume)
			{
				DPE_SetAlpha(1.0);
				DPE_SetBright(0.8, 1, 1);
				DrawRect(P_WHITEBOX, dr_l, dr_t, volume, dr_h);
			}
			DPE_Reset();
		}

		EachFrame();
	}
	FreezeInput();
}
static void SettingMenu(void)
{
	const int selectMax = 7;
	int selectIndex = 0;

	FreezeInput();

	for(; ; )
	{
		if(GetPound(INP_DIR_8))
			selectIndex--;

		if(GetPound(INP_DIR_2))
			selectIndex++;

		if(GetPound(INP_B))
		{
			if(selectIndex == selectMax - 1)
				break;

			selectIndex = selectMax - 1;
		}
		m_range(selectIndex, 0, selectMax - 1);

		if(GetPound(INP_A))
		{
			switch(selectIndex)
			{
			case 0:
				SM_PadConfig();
				break;

			case 1:
				SM_WindowSizeSetting();
				break;

			case 2:
				SM_VolumeSetting(0);
				break;

			case 3:
				SM_VolumeSetting(1);
				break;

			case 4:
				SetMouseDispMode(GetMouseDispMode() ? 0 : 1);
				break;

			case 5:
				Gnd.FastBtnReverseMode = Gnd.FastBtnReverseMode ? 0 : 1;
				break;

			case 6:
				goto endLoop;

			default:
				error();
			}
		}
		DrawTitleWall_Curtain();

		PE_Border(GetColor(0, 100, 0));
		SetPrint(60, 150, 40);
		Print("設定");
		PrintRet();
		int c = 0;
		Print_x(xcout("[%c]　パッドのボタン設定", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　ウィンドウサイズの変更", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　ＢＧＭボリューム設定", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　ＳＥボリューム設定", selectIndex == c++ ? '>' : ' '));
		PrintRet();
		Print_x(xcout("[%c]　マウスカーソル [ %s ]", selectIndex == c++ ? '>' : ' ', GetMouseDispMode() ? "表示" : "非表示"));
		PrintRet();
		Print_x(xcout("[%c]　高速移動ボタンを離しているとき高速にする [ %s ]", selectIndex == c++ ? '>' : ' ', Gnd.FastBtnReverseMode ? "有効" : "無効"));
		PrintRet();
		Print_x(xcout("[%c]　戻る", selectIndex == c++ ? '>' : ' '));
		PE_Reset();

		EachFrame();
	}
endLoop:
	FreezeInput();
}

// ----

static void LeaveMainMenu(void)
{
	MusicFade();
	SetCurtain(30, -1.0);

	forscene(40)
	{
		DrawTitleWall();
		EachFrame();
	}
	sceneLeave();

	Gnd.EL->Clear();
}
static void ReturnMainMenu(void)
{
	1; // noop
}
static void StartNewGame(void)
{
	GameInit();

//	GDc.MapFile = strx("..\\..\\map\\0001.bmp"); // test
	GDc.MapFileData = GetEtcRes()->GetHandle(ETC_MAP_0001);

	GameMain();
	GameFnlz();
}
static void ContinueGame(void)
{
	GameInit();
	GameMain();
	GameFnlz();
}
static void ContinueGame_NoData(void)
{
	FreezeInput();

	for(; ; )
	{
		if(
			GetInput(INP_A) == 1 ||
			GetInput(INP_B) == 1
			)
			break;

		DrawTitleWall_Curtain();

		PE_Border(GetColor(96, 0, 0));
		SetPrint(60, 290);
		Print("セーブデータがありません...");
		PE_Reset();

		EachFrame();
	}
	FreezeInput();
}

// ----

typedef struct ItemPos_st
{
	double X;
	double Y;
	double A;
	double RealX;
	double RealY;
	double RealA;
}
ItemPos_t;

#define ITEM_MAX 4

static ItemPos_t ItemPosList[ITEM_MAX];

void MainMenu(void)
{
	int selectIndex = 0;

	if(0)
		selectIndex = 1;

restart:
	ActFrame = 0;
	FreezeInput();

	MusicPlay(MUS_TITLE);
	SetCurtain(30, -1.0, -1.0);
	SetCurtain(30, 0.0, -1.0);

	const double ITEM_UNSEL_X = 120.0;
	const double ITEM_UNSEL_A = 0.5;
	const double ITEM_SEL_X = 140.0;
	const double ITEM_SEL_A = 1.0;
	const double ITEM_Y = 225.0;
	const double ITEM_Y_STEP = 50.0;

	for(int index = 0; index < ITEM_MAX; index++)
	{
		ItemPos_t *i = ItemPosList + index;

		i->X = ITEM_UNSEL_X;
		i->Y = ITEM_Y + index * ITEM_Y_STEP;
		i->A = ITEM_UNSEL_A;
		i->RealX = -100.0 - index * 200.0;
		i->RealY = i->Y;
		i->RealA = ITEM_UNSEL_A;
	}
	for(; ; )
	{
		if(GetPound(INP_DIR_8))
			selectIndex--;

		if(GetPound(INP_DIR_2))
			selectIndex++;

		m_range(selectIndex, 0, ITEM_MAX - 1);

		if(GetPound(INP_A))
		{
			switch(selectIndex)
			{
			case 0:
				LeaveMainMenu();
				StartNewGame();
				ReturnMainMenu();
				goto restart;

			case 1:
				if(0)
				{
					LeaveMainMenu();
					ContinueGame();
					ReturnMainMenu();
					goto restart;
				}
				SetCurtain(30, -0.5);
				ContinueGame_NoData();
				SetCurtain();
				break;

			case 2:
				SetCurtain(30, -0.5);
				SettingMenu();
				SetCurtain();
				break;

			case 3:
				goto endMenu;

			default:
				error();
			}
		}
		if(GetPound(INP_B))
		{
			if(selectIndex == ITEM_MAX - 1)
				break;

			selectIndex = ITEM_MAX - 1;
		}
		DrawTitleWall();

		for(int index = 0; index < ITEM_MAX; index++)
		{
			ItemPos_t *i = ItemPosList + index;

			i->X = index == selectIndex ? ITEM_SEL_X : ITEM_UNSEL_X;
			i->A = index == selectIndex ? ITEM_SEL_A : ITEM_UNSEL_A;

			m_approach(i->RealX, i->X, 0.93);
			m_approach(i->RealY, i->Y, 0.93);
			m_approach(i->RealA, i->A, 0.93);

			DPE_SetAlpha(i->RealA);
			DrawCenter(D_TITLEITEM_00 + index | DTP, i->RealX, i->RealY);
			DPE_Reset();
		}
		EachFrame();
	}
endMenu:
	MusicFade();
	SetCurtain(30, -1.0);

	forscene(40)
	{
		DrawTitleWall();
		EachFrame();
	}
	sceneLeave();
}
