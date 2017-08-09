/*
	zd ... zero disabled

	float, double をゼロクリアした値・広域変数の初期値は 0.0 とする。
	float, double の計算結果は環境によって誤差があるものとする。

	----
	ゲームループの基本形

//	ActFrame = 0; // 必要ならば
	FreezeInput();

	for(; ; )
	{
		1. 処理
			ループの脱出
			割り込み処理
				離脱処理・再入処理はここで行う？
				FreezeInput();
		2. 描画
		3. EachFrame();
	}
//	FreezeInput(); // 念のため
*/

#include "all.h"

void ProcMain(void)
{
#if !LOG_ENABLED // product
	Logo();
	MainMenu();
#elif 0 // test
	{
		GameInit();
		GDc.MapFile = strx("..\\..\\map\\0001.bmp");
		GameMain();
		GameFnlz();
	}
#elif 0 // test
	MainMenu();
#else // test
	Logo();
	MainMenu();
#endif
}
